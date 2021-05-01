#pragma once
#define BALLMAX 40

//속도: 방향과 크기   (벡터)
//속력: 크기   자동차계기판 km/1h (스칼라)

struct Ball
{
    Circle* cc;

    Vector2 dir; //쏘는방향
    float   speed = 200.0f; //속력
    

    Vector2 velocity; //속도
    float   gravity;  //중력


    // 속도 = 방향* 속력
    //  v   =  v * k
};

class Scene2 : public Scene
{
private:
    Ball bl[BALLMAX];
    Rect* pl;
    Line* cannon;
    Object* FirePos;//발사위치
    float   cor = 1.0f; //반발계수

public:
    HRESULT Init() override;//초기화
    void Release() override;//해제


    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

