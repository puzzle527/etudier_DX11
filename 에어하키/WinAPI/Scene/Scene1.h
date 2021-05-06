#pragma once

enum TURN
{
    PLAYER1,     //조작가능한 페이즈
    PLAYER1_FIRE,//발사
    PLAYER2,
    PLAYER2_FIRE,
};


struct Player
{
    //오브젝트
    Rect* body;
    Line* cannon;
    Object* fire;
    Rect* gauge;

    //멤버
    float power;
    int   hp;
    float angle;
    Player()
    {
        hp = 100;
        power = 0.0f;
        angle = 0.0f;
    }

};

class Scene1 : public Scene
{
  
private:

    Player  pl[2];

    int     turn;

    //조종할 플레이어
    Player* Control;

    //ball의 멤버
    Circle* ball;
    Vector2 ballDir;
    float   ballSpeed;
    Vector2 ballVelocity;

public:
    HRESULT Init() override;
    void Release() override;

    void Update() override;
    void LateUpdate() override;
    void Render() override;
};

