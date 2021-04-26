#pragma once
class Scene2 : public Scene
{
private:

    Rect* cc;
    Rect* cc1;
    Vector2 LastMouse; //이전프레임의 마우스 좌표

public:
    HRESULT Init() override;//초기화
    void Release() override;//해제


    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

