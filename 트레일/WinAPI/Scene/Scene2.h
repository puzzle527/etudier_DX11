#pragma once
#define PLMAXSPEED 400.0f
#define PLMINSPEED 50.0f

struct PLYAER
{
    Circle* cc;
    float   speed;//속력
    Rect*   goal; //골
    int     score;//점수
    Vector2 dir;//방향
};
class Scene2 : public Scene
{
private:
    PLYAER      pl[2];
    Line*       center;

    Circle*     ball;
    Vector2     ballDir; //쏘는방향
    float       ballSpeed; //속력


public:
    void Reset();
    HRESULT Init() override;//초기화
    void Release() override;//해제


    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

