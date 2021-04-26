#pragma once
#define DROPMAX 30
#define BGMAX 30

struct DROP
{
    Circle* cc;
    float   Speed;
    //float   Seta;
    Vector2 Dir;


    //떨어지거나 생성했을때 위치,스피드 재배치
    void Reset(Vector2 pos) //기준이되는 위치
    {
        //0~360사이 난수
        float Seta = RndFloat(0.0f, 2.0f * PI);
        //사이각을 통해 멀어진 좌표
        cc->Position = pos + 
            Vector2(cosf(Seta), sinf(Seta)) * 
            (500.0f +RndFloat(50.0f,200.0f));
        //사이각 오차발생
        Seta += RndFloat(-0.5f,0.5f);
        //반대 사이각으로 방향 정하기
        Dir = -Vector2(cosf(Seta), sinf(Seta));
        Speed = RndFloat(100.0f, 400.0f);
        cc->color = Color(RndFloat(), RndFloat(), RndFloat(), 1.0f);
    }
};

class Scene1 : public Scene
{
private:
    Rect* player;
    DROP  dr[DROPMAX];
    float timeScale = 1.0f;
    Star* bg[BGMAX]; //배경
    int   Score = 0;
public:
    HRESULT Init() override;//초기화
    void Release() override;//해제

    
    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

