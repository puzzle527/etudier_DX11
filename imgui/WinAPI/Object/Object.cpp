#include "stdafx.h"
#include "Object.h"

//��������� cpp �������� ȣ���Ͽ� �ʱ�ȭ
Line* Object::Axis = nullptr;

Object::Object()
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

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &WBuffer);
        assert(SUCCEEDED(hr));
    }
    //�������
    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Color);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�������
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &ColorBuffer);
        assert(SUCCEEDED(hr));
    }
    P = nullptr;
}

Object::~Object()
{
    SAFE_RELEASE(WBuffer);
    SAFE_RELEASE(ColorBuffer);
    SAFE_DELETE(shader);
}

void Object::Init()
{
    Position = Vector2(0.0f, 0.0f);
    Scale = Vector2(1.0f, 1.0f);
    Rotation = 0.0f;
    Rotation2 = 0.0f;
    Up = Vector2(0.0f, 1.0f);
    Right = Vector2(1.0f, 0.0f);

}

void Object::WorldUpdate()
{
    //ũ�� ���
    D3DXMatrixScaling(&S, Scale.x
        , Scale.y, 0);
    //ȸ�� ���
    D3DXMatrixRotationZ(&R, Rotation);
    D3DXMatrixRotationZ(&R2, Rotation2);

    //�̵������ ������Լ�
    D3DXMatrixTranslation(&T, Position.x
        , Position.y, 0);
    //������� �����
    W = S * R * T * R2;
    //ȸ�� �̵���� �����
    RT = R * T * R2;

    //�θ� �����Ѵٸ�
    if(P)
    {
        W *= *P;
        RT *= *P;
    }



    Right = Vector2(RT._11, RT._12);
    Up = Vector2(RT._21, RT._22);

    //w = 0
    D3DXVec2TransformNormal(
        &WorldPivot, &Pivot, &W);
}

void Object::Render()
{
    if(isAxis)
    {
        //right
        Axis->Position = Vector2(W._41, W._42);
        Axis->Rotation = DirToRadian(Right);
        Axis->Scale.x = Scale.x;
        Axis->WorldUpdate();
        Axis->Render();
        //up
        Axis->Position = Vector2(W._41, W._42);
        Axis->Rotation = DirToRadian(Up);
        Axis->Scale.x = Scale.y;
        Axis->WorldUpdate();
        Axis->Render();
    }
    //������� ������Ʈ W���� WBuffer�� ����
    g_DeviceContext->UpdateSubresource(WBuffer, 0, NULL, &W, 0, 0);
    //                            ����ɷ������� ��ȣ 0
    g_DeviceContext->VSSetConstantBuffers(0, 1, &WBuffer);

    g_DeviceContext->UpdateSubresource(ColorBuffer, 0, NULL, &color, 0, 0);
    //                            ����ɷ������� ��ȣ 3
    g_DeviceContext->VSSetConstantBuffers(3, 1, &ColorBuffer);


}
