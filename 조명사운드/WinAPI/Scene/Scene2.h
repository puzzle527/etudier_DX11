#pragma once

struct ShootPlayer
{
    Image*  Move;
    Image*  Boost;
    Circle* Body;
    int     State;
    float   Handle = 0.0f; //좌 -,우 +,중립 0
};

class Scene2 : public Scene
{
private:
    Image* Bg;
    ShootPlayer Pl;
    float  BgmScale;
    bool   isFadeout;
    float  FadeoutTime;

    bool   isFadein;
    float  FadeinTime;
public:
    Scene2();
    ~Scene2();

    HRESULT Init() override;//초기화
    void Release() override;//해제


    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

