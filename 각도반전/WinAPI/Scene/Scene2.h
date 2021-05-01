#pragma once
#define BALLMAX 40
struct Ball
{
    Circle* cc;
    //Vector2 dir;
    float   speed = 100.0f;

};

class Scene2 : public Scene
{
private:
    Ball bl[BALLMAX];
    Rect* pl;
    Line* cannon;
    Object* FirePos;//발사위치

public:
    HRESULT Init() override;//초기화
    void Release() override;//해제


    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

