#pragma once
class Transform
{
    //4차원은 시간축이 더해진 
    //X    w= 동차
    //벡터 x 행렬을 곱할때도 필요
    Matrix S, R, T;
public:
    Matrix W;
    Transform();
    static ID3D11Buffer* WBuffer;
    static void CreateBuffer();
    static void ReleaseBuffer();
    Vector3 position; //위치
    Vector3 rotation; //회전각도(3축회전값)
    Vector3 scale; //크기(배율)
    virtual void Update(Matrix* P = nullptr);
    virtual void Set();
    virtual bool ImGuiRender();
};

