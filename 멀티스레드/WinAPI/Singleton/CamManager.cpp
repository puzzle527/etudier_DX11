#include "stdafx.h"
#include "CamManager.h"

CamManager::CamManager()
{
    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Matrix);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�������
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &VBuffer);
        assert(SUCCEEDED(hr));
    }

    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Matrix);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�������
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &PBuffer);
        assert(SUCCEEDED(hr));
    }

    //�������� ������ִ� �Լ�
    //                             ��    �� 
    D3DXMatrixOrthoOffCenterLH(&P, 0, (float)WINSIZEX,
        //  �Ʒ�, ��           ������,�ָ��ִ¸�
        0, (float)WINSIZEY, 0, 10);
    //2D������ ���ٰ��� ǥ������ �ʱ⿡ ���������� ������� �ʴ´�


    //ù ī�޶� ��ġ
    Pos.x = 0.0f;
    Pos.y = 0.0f;
}

CamManager::~CamManager()
{
    SAFE_RELEASE(VBuffer);
    SAFE_RELEASE(PBuffer);
}

void CamManager::CameraUpdate()
{
    Vector3 eye =
        Vector3(Pos.x, Pos.y, -1.0f);
    Vector3 look =
        Vector3(Pos.x, Pos.y, 0.0f);
    Vector3 up =
        Vector3(0.0f, 1.0f, 0.0f);
    //View �� ����
    D3DXMatrixLookAtLH(&V,
        &eye,//eye(������ġ)
        &look,//at(�ٶ󺸴� ��ġ)
        &up); //up(ī�޶� �����ٶ󺸴¹���)


    g_DeviceContext->UpdateSubresource(VBuffer, 0, NULL, &V, 0, 0);
    //                            ����ɷ������� ��ȣ 1
    g_DeviceContext->VSSetConstantBuffers(1, 1, &VBuffer);


    g_DeviceContext->UpdateSubresource(PBuffer, 0, NULL, &P, 0, 0);
    //                            ����ɷ������� ��ȣ 1
    g_DeviceContext->VSSetConstantBuffers(2, 1, &PBuffer);


}
