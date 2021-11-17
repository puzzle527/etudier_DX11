#pragma once
class Tile;
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
    float RollTime;
    void SetLook(Vector2 Dir, Image* target);
    Vector2 Foot;       //타일과 충돌할 지점
    //길찾기용 변수
    vector<Tile*> way;

    Vector2 from;
    Vector2 to;
    float   g;
public:
    Player();
    ~Player();

    HRESULT Init();//초기화
    void Release();//해제

    void Update();//갱신
    void LateUpdate();//늦은갱신
    void Render();//그리기
    void Move(bool dir = true);
    void Move2();
    vector<Tile*>& GetWay() { return way; }
    MAKEGET(Rect*, body)
    MAKEGET(Vector2, Foot)
    MAKESET(Vector2 ,from)
    MAKESET(Vector2 ,to)
    MAKESET(float  , g)
};

