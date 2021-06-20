#pragma once
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

    void SetLook(Vector2 Dir, Image* target);
public:
    Player();
    ~Player();

    HRESULT Init();//�ʱ�ȭ
    void Release();//����

    void Update();//����
    void LateUpdate();//��������
    void Render();//�׸���
};

