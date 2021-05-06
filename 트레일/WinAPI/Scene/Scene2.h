#pragma once
#define PLMAXSPEED 400.0f
#define PLMINSPEED 50.0f

struct PLYAER
{
    Circle* cc;
    float   speed;//�ӷ�
    Rect*   goal; //��
    int     score;//����
    Vector2 dir;//����
};
class Scene2 : public Scene
{
private:
    PLYAER      pl[2];
    Line*       center;

    Circle*     ball;
    Vector2     ballDir; //��¹���
    float       ballSpeed; //�ӷ�


public:
    void Reset();
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����


    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

