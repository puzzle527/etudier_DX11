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
    //SAFE_RELEASE(ColorBuffer);
    SAFE_DELETE(shader);
}

void Object::Init()
{
    Position = Vector2(0.0f,0.0f);
    Scale = Vector2(1.0f,1.0f);
    Rotation = Vector3(0.0f, 0.0f, 0.0f);
    Rotation2 = Vector3(0.0f, 0.0f, 0.0f);
    Up = Vector2(0.0f, 1.0f);
    Right = Vector2(1.0f, 0.0f);
  
}

void Object::WorldUpdate()
{
    if (!isActive)return;


    //ũ�� ���
    D3DXMatrixScaling(&S, Scale.x
        , Scale.y, 0);
    //ȸ�� ���
    D3DXMatrixRotationYawPitchRoll(&R, Rotation.y, Rotation.x, Rotation.z);
    D3DXMatrixRotationYawPitchRoll(&R2, Rotation2.y, Rotation2.x, Rotation2.z);

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

    //Pivot
          //w = 0
        D3DXVec2TransformNormal(
                &WorldPivot, &Pivot, &S);
        D3DXVec2TransformNormal(
            &WorldPivot, &WorldPivot, &RT);
        //D3DXVec2TransformCoord();
    //Up = Vector2(0.0f, 1.0f);
    //D3DXVec2TransformNormal(
    //    &Up, &Up, &RT);
    ////   Up = Up * R

    ////��������Ÿ���� ���ʹ� ���� 0
    //Right = Vector2(1.0f, 0.0f);
    //D3DXVec2TransformNormal(
    //    &Right, &Right, &RT);
    //   Right = Right * R

}

void Object::Render()
{
    if (!isActive)return;

    if(isAxis)
    {
        //right
        Axis->Position = Vector2(W._41, W._42);
        Axis->Rotation.z = DirToRadian(Right);
        Axis->Scale.x = Scale.x;
        Axis->WorldUpdate();
        Axis->Render();
        //up
        Axis->Position = Vector2(W._41, W._42);
        Axis->Rotation.z = DirToRadian(Up);
        Axis->Scale.x = Scale.y;
        Axis->WorldUpdate();
        Axis->Render();
    }
    //������� ������Ʈ W���� WBuffer�� ����
    g_DeviceContext->UpdateSubresource(WBuffer, 0, NULL, &W, 0, 0);
    //                            ����ɷ������� ��ȣ 0
    g_DeviceContext->VSSetConstantBuffers(0, 1, &WBuffer);


    g_DeviceContext->UpdateSubresource(ColorBuffer, 0, NULL, &color, 0, 0);
    //                            ����ɷ������� ��ȣ 0
    g_DeviceContext->VSSetConstantBuffers(3, 1, &ColorBuffer);


}
