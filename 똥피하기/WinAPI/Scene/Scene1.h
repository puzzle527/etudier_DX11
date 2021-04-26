#pragma once
#define DDMAX 50
#define BGMAX 30

class DD
{
public:
    Circle* cc;
    float speed;
    Vector2 dir;
    float lifeTime;
    void Reset(Vector2 Pos);

};


class Scene1 : public Scene
{
    //friend class DD;
private:
    Rect* pl;       //얘가 움직일 플레이어
    Circle* child[2];

    //에딧할 값
    float   Distance; //멀어질 거리
    float   Radius;   //반지름
    float   Speed;    //회전속도


    DD    dd[DDMAX];//떨어질 DD

    Star* bg[BGMAX]; //배경

    //시간크기값
    float timeScale = 1.0f;
    int   count = 0;

public:
    HRESULT Init() override;
    void Release() override;

    void Update() override;
    void LateUpdate() override;
    void Render() override;
};

