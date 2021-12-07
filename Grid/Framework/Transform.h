#pragma once
class Transform
{
    //4차원은 시간축이 더해진 
    //X    w= 동차
    //벡터 x 행렬을 곱할때도 필요
public:
    Matrix S, R, T, RT;
    Matrix W;
    Vector3 position; //위치
    Vector3 rotation; //회전각도(3축회전값)
    Vector3 scale; //크기(배율)
    Transform();
    static ID3D11Buffer* WBuffer;
    static void CreateBuffer();
    static void ReleaseBuffer();
    virtual void Update(Transform* P = nullptr);
    virtual void Set();
    virtual bool ImGuiRender();
    Vector3 Forward() { return Vector3(RT._31, RT._32, RT._33); }
    Vector3 Up() { return Vector3(RT._21, RT._22, RT._23); }
    Vector3 Right() { return Vector3(RT._11, RT._12, RT._13); }
    Vector3 WorldPos() { return Vector3(W._41, W._42, W._43); }
};

