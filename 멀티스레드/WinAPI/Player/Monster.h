#pragma once
enum MON_STATE
{
    MON_IDLE, //대기
    MON_LOOK = 600,
    MON_MOVE = 350,
    MON_ATTACK = 150
};
class Monster
{
private:
    enum
    {
        MON_IMG_R, MON_IMG_L, MON_IMG_RD, MON_IMG_LU,
        MON_IMG_U, MON_IMG_D, MON_IMG_LD, MON_IMG_RU
    };
    Rect* body;
    Image* head;
    int state;
    Vector2 LookDir;    //
    Circle* DebugRender;
    class Player* pl;
    float AttTime;
    void SetLook(Vector2 Dir, Image* target);
public:
    Monster();
    ~Monster();

    HRESULT Init();//초기화
    void Release();//해제

    void Update();//갱신
    void LateUpdate();//늦은갱신
    void Render();//그리기
    MAKEGET(Rect*, body)
    MAKESET(Player*, pl)
};
