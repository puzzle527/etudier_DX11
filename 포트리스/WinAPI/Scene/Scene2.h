#pragma once



struct PLYAER
{
    Circle* cc;
    Line*   cannon;
    Object* fire;
    Rect*   gauge;
    int     hp;//피
    Vector2 dir;//방향
    float   power;//쏘는힘
};
class Scene2 : public Scene
{
private:
    Image* bono1;


    // 익명 enum
    //클래스내부에서만 쓸수있다.
    //type으로 사용불가
    enum 
    {
        PLAYER1P,     //조작턴
        PLAYER1P_FIRE,//발사턴
        PLAYER2P,
        PLAYER2P_FIRE

    };
    PLYAER      pl[2];
    //조작할 플레이어
    PLYAER* CurrentPl;


    Circle*     ball;
    Vector2     ballDir; //쏘는방향
    float       ballSpeed; //속력
    float       ballGravity; //공의 중력
    int         turn;
    float       fireTime;

public:
    HRESULT Init() override;//초기화
    void Release() override;//해제


    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

