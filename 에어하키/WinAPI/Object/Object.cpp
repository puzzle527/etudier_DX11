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


    //크기 행렬
    D3DXMatrixScaling(&S, Scale.x
        , Scale.y, 0);
    //회전 행렬
    D3DXMatrixRotationYawPitchRoll(&R, Rotation.y, Rotation.x, Rotation.z);
    D3DXMatrixRotationYawPitchRoll(&R2, Rotation2.y, Rotation2.x, Rotation2.z);

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

    ////방향을나타내는 벡터는 동차 0
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
    //상수버퍼 업데이트 W값을 WBuffer에 전달
    g_DeviceContext->UpdateSubresource(WBuffer, 0, NULL, &W, 0, 0);
    //                            연결될레지스터 번호 0
    g_DeviceContext->VSSetConstantBuffers(0, 1, &WBuffer);


    g_DeviceContext->UpdateSubresource(ColorBuffer, 0, NULL, &color, 0, 0);
    //                            연결될레지스터 번호 0
    g_DeviceContext->VSSetConstantBuffers(3, 1, &ColorBuffer);


}
