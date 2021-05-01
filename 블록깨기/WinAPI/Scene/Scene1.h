#pragma once
#define ROWCOUNT 20
#define COLCOUNT 3
#define BLOCKMAX ROWCOUNT*COLCOUNT

struct BLOCK
{
    Rect* rc;
    int   life;
};

class Scene1 : public Scene
{
private:
    BLOCK bl[BLOCKMAX];
    Rect* pl;

    Circle* ball;
    Vector2 ballDir; //쏘는방향
    float   ballSpeed = 200.0f; //속력
    float   cor;
public:
    HRESULT Init() override;//초기화
    void Release() override;//해제

    
    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

