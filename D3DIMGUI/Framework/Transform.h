#pragma once
class Transform
{
    //4차원은 시간축이 더해진 
    //X    w= 동차
    //벡터 x 행렬을 곱할때도 필요
public:
    Transform();
    Vector3 position; //위치
    Vector3 rotation; //회전각도(3축회전값)
    Vector3 scale; //크기(배율)

    virtual void ImGuiRender();
};

