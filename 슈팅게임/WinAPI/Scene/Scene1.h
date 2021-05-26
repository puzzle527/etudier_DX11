#pragma once

enum RunPlayerState
{
    RPL_RUN,
    RPL_JUMP,
    RPL_SLIDE,
};

struct RunPlayer
{
    Image* Run;
    Image* Spin;
    Rect* Body;
    int    State;
    float  Gravity;
};


class Scene1 : public Scene
{
private:

    Image* Bg; //구름
    Image* Floor;//바닥
    RunPlayer Pl;

public:
    HRESULT Init() override;//초기화
    void Release() override;//해제
    
    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

