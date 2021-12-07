#include "Framework.h"
#include "Camera.h"

Camera::Camera(string Name)
    : Actor(Name)
{
    Fov = XM_PI / 3.0f;
    Near = 0.01f;
    Far = 1000000.0f;
    type = OBTYPE::CAM;
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

void Camera::CamImGuiRender()
{
    ImGui::DragFloat("Fov", &Fov, 0.05f);
    ImGui::DragFloat("Near", &Near, 0.05f);
    ImGui::DragFloat("Far", &Far, 0.05f);
}

void Camera::Update()
{
    GameObject::Update();

    Proj = Matrix::CreatePerspectiveFieldOfView(
      Fov, D3D->Width() / D3D->Height(),Near, Far);

    View = RT.Invert();
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
