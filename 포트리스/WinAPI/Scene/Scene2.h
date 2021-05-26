#pragma once



struct PLYAER
{
    Circle* cc;
    Line*   cannon;
    Object* fire;
    Rect*   gauge;
    int     hp;//��
    Vector2 dir;//����
    float   power;//�����
};
class Scene2 : public Scene
{
private:
    Image* bono1;


    // �͸� enum
    //Ŭ�������ο����� �����ִ�.
    //type���� ���Ұ�
    enum 
    {
        PLAYER1P,     //������
        PLAYER1P_FIRE,//�߻���
        PLAYER2P,
        PLAYER2P_FIRE

    };
    PLYAER      pl[2];
    //������ �÷��̾�
    PLYAER* CurrentPl;


    Circle*     ball;
    Vector2     ballDir; //��¹���
    float       ballSpeed; //�ӷ�
    float       ballGravity; //���� �߷�
    int         turn;
    float       fireTime;

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����


    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

