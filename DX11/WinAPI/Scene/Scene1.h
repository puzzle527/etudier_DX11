#pragma once
#define BULLETMAX 100

struct BULLET
{
    Vector2 Pos; //위치
    Vector2 Dir; //방향
    float   Speed; // 속도


    float   Rot; //공전 회전값
    bool    isFire; //발사했는가?
    BULLET()
    {
        Pos = Vector2(0.0f,0.0f);
        Dir = Vector2(1.0f,0.0f);//0
        isFire = false;
        Rot = 0.0f;
    }
};

class Scene1 : public Scene
{
private:
    Rect* child;
    Rect* child2;
    Rect* rc;
    float rcSpeed; //rc이동속도

    Object* ln; //총알을 그려줄 라인
    Circle* lnChild; //총알을 공전하는객체
    BULLET bl[BULLETMAX]; //얘가 총알
public:
    HRESULT Init() override;//초기화
    void Release() override;//해제

    
    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

