#pragma once
#define TRAILMAX 5

class Scene1 : public Scene
{
private:
    Image* bono1;
    Rect*  bono1rc;     //충돌용 오브젝트


    Image* bono2;
    Circle* bono2cc;    //충돌용 오브젝트

public:
    HRESULT Init() override;//초기화
    void Release() override;//해제
    
    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

