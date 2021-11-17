#include "Framework.h"
#include "Camera.h"

Camera::Camera(string Name)
    : GameObject(Name)
{
}

Camera::~Camera()
{
}

Camera* Camera::Create(string Name)
{
    return new Camera(Name);
}
ID3D11Buffer* Camera::VBuffer = nullptr;
ID3D11Buffer* Camera::PBuffer = nullptr;
void Camera::CreateBuffer()
{
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(Matrix);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &VBuffer);
        assert(SUCCEEDED(hr));
    }
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(Matrix);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &PBuffer);
        assert(SUCCEEDED(hr));
    }

}

void Camera::ReleaseBuffer()
{
    SafeRelease(VBuffer);
    SafeRelease(PBuffer);
}

bool Camera::ImGuiRender()
{
    ImGui::Text("ImCam");

    return GameObject::ImGuiRender();
}

void Camera::Update()
{
    GameObject::Update();

    Proj = Matrix::CreatePerspectiveFieldOfView(
        XM_PI / 3.0f, D3D->Width() / D3D->Height(), 0.01f, 1000.0f);;

    Matrix R, T;
    R = Matrix::CreateFromYawPitchRoll(-rotation.y, -rotation.x, -rotation.z);
    T = Matrix::CreateTranslation(-position.x, -position.y, -position.z);

    View = T * R;
}

void Camera::Set()
{
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        Matrix* dataPtr;
        D3D->GetDC()->Map(VBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        dataPtr = (Matrix*)mappedResource.pData;
        //복사(쓰기)
        *dataPtr = View;
        D3D->GetDC()->Unmap(VBuffer, 0);
        D3D->GetDC()->VSSetConstantBuffers(1, 1, &VBuffer);
    }
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        Matrix* dataPtr;
        D3D->GetDC()->Map(PBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        dataPtr = (Matrix*)mappedResource.pData;
        //복사(쓰기)
        *dataPtr = Proj;
        D3D->GetDC()->Unmap(PBuffer, 0);
        D3D->GetDC()->VSSetConstantBuffers(2, 1, &PBuffer);
    }
}
