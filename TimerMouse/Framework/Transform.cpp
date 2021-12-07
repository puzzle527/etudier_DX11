#include "Framework.h"
#include "Transform.h"

Transform::Transform()//: scale(1.0f, 1.0f, 1.0f)
{
    //scale.x = 1.0f;
    //scale.y = 1.0f;
    //scale.z = 1.0f;
    //scale.x = scale.y = scale.z = 1.0f;
    scale = Vector3(1.0f, 1.0f, 1.0f);
}
ID3D11Buffer* Transform::WBuffer = nullptr;
void Transform::CreateBuffer()
{
    D3D11_BUFFER_DESC desc = { 0 };
    desc.ByteWidth = sizeof(Matrix);
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;
    HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &WBuffer);
    assert(SUCCEEDED(hr));
}

void Transform::ReleaseBuffer()
{
    SafeRelease(WBuffer);
}


void Transform::Update(Transform* P)
{
    //position.Length();
    //position.LengthSquared();

    S = Matrix::CreateScale(scale.x, scale.y, scale.z);
    //R = Matrix::CreateFromQuaternion(
    //    Quaternion::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z));
    R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
    T = Matrix::CreateTranslation(position.x, position.y, position.z);

    RT = R * T;
    W = S * RT;
    if (P)
    {
        W = W * P->W;
        RT = RT * P->RT;
    }

}

void Transform::Set()
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    Matrix* dataPtr;
    D3D->GetDC()->Map(WBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    dataPtr = (Matrix*)mappedResource.pData;
    //복사(쓰기)
    *dataPtr = W;
    D3D->GetDC()->Unmap(WBuffer, 0);
    D3D->GetDC()->VSSetConstantBuffers(0, 1, &WBuffer);
}

bool Transform::ImGuiRender()
{
    //rot,scale,pos
    //float a[3]; 
    /*if (ImGui::CollapsingHeader("Transform"))
    {
       
    }*/
    //ImGui::DragFloat3()
    ImGui::DragFloat3("Pos", (float*)&position,0.005f);
    ImGui::DragFloat3("Scale", (float*)&scale, 0.005f);
    ImGui::DragFloat3("Rot", (float*)&rotation, 0.005f);
    return true;
}
