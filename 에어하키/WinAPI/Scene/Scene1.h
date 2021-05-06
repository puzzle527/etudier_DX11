#pragma once

enum TURN
{
    PLAYER1,     //���۰����� ������
    PLAYER1_FIRE,//�߻�
    PLAYER2,
    PLAYER2_FIRE,
};


struct Player
{
    //������Ʈ
    Rect* body;
    Line* cannon;
    Object* fire;
    Rect* gauge;

    //���
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

    //������ �÷��̾�
    Player* Control;

    //ball�� ���
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

