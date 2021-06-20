#pragma once
class Tile;
enum PL_STATE
{
    PL_IDLE, //���
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
    Vector2 InputDir;   //�Է¹���
    Vector2 LookDir;    //���콺����
    float RollTime;
    void SetLook(Vector2 Dir, Image* target);
    Vector2 Foot;       //Ÿ�ϰ� �浹�� ����
    //��ã��� ����
    vector<Tile*> way;

    Vector2 from;
    Vector2 to;
    float   g;
public:
    Player();
    ~Player();

    HRESULT Init();//�ʱ�ȭ
    void Release();//����

    void Update();//����
    void LateUpdate();//��������
    void Render();//�׸���
    void Move(bool dir = true);
    void Move2();
    vector<Tile*>& GetWay() { return way; }
    MAKEGET(Rect*, body)
    MAKEGET(Vector2, Foot)
    MAKESET(Vector2 ,from)
    MAKESET(Vector2 ,to)
    MAKESET(float  , g)
};

