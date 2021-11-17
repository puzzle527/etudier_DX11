#include "stdafx.h"
#include "LightManager.h"

LightManager::LightManager()
{
    light.ScreenPos =
        Vector2(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
    light.Radius = WINSIZEX * 3.5f;
    light.LightColor = Color(0.5f, 0.5f, 0.5f, 0.5f);

    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Light);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�������
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &LightBuffer);
        assert(SUCCEEDED(hr));
    }
}

LightManager::~LightManager()
{
    SAFE_RELEASE(LightBuffer);
}

void LightManager::LightUpdate()
{
    //�ӽ� ���� �����
    ImGui::SliderFloat2("LIGHTPOS",
        light.ScreenPos, -800.0f, 800.0f);
    ImGui::SliderFloat("LIGHTRADIUS",
        &light.Radius, 0.0f, 1200.0f);
    ImGui::ColorEdit4("LIGHTCOLOR",
        light.LightColor);




    g_DeviceContext->UpdateSubresource(LightBuffer, 0, NULL, &light, 0, 0);
    //                            ����ɷ������� ��ȣ 0
    g_DeviceContext->PSSetConstantBuffers(0, 1, &LightBuffer);
}
