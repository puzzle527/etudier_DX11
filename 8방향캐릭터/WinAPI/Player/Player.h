#pragma once
enum PL_STATE
{
    PL_IDLE, //대기
    PL_WALK,
    PL_ROLL
};
class Player
{
private:
    enum
    {
        PL_IMG_R, PL_IMG_U, PL_IMG_L, PL_IMG_D,
        PL_IMG_RD, PL_IMG_LD, PL_IMG_LU, PL_IMG_RU
    };
    Rect* body;
    Image* walk;
    Image* roll;
    int state;
    Vector2 InputDir;   //입력방향
    Vector2 LookDir;    //마우스방향

    void SetLook(Vector2 Dir, Image* target);
public:
    Player();
    ~Player();

    HRESULT Init();//초기화
    void Release();//해제

    void Update();//갱신
    void LateUpdate();//늦은갱신
    void Render();//그리기
};

