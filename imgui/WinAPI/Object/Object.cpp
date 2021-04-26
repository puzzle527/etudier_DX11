#include "stdafx.h"
#include "Object.h"

//정적멤버는 cpp 전역에서 호출하여 초기화
Line* Object::Axis = nullptr;

Object::Object()
{
    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Matrix);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &WBuffer);
        assert(SUCCEEDED(hr));
    }
    //상수버퍼
    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Color);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
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
    //크기 행렬
    D3DXMatrixScaling(&S, Scale.x
        , Scale.y, 0);
    //회전 행렬
    D3DXMatrixRotationZ(&R, Rotation);
    D3DXMatrixRotationZ(&R2, Rotation2);

    //이동행렬을 만드는함수
    D3DXMatrixTranslation(&T, Position.x
        , Position.y, 0);
    //최종행렬 만들기
    W = S * R * T * R2;
    //회전 이동행렬 만들기
    RT = R * T * R2;

    //부모가 존재한다면
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
    //상수버퍼 업데이트 W값을 WBuffer에 전달
    g_DeviceContext->UpdateSubresource(WBuffer, 0, NULL, &W, 0, 0);
    //                            연결될레지스터 번호 0
    g_DeviceContext->VSSetConstantBuffers(0, 1, &WBuffer);

    g_DeviceContext->UpdateSubresource(ColorBuffer, 0, NULL, &color, 0, 0);
    //                            연결될레지스터 번호 3
    g_DeviceContext->VSSetConstantBuffers(3, 1, &ColorBuffer);


}
