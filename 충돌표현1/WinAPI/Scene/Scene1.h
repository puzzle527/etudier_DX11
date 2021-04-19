#pragma once
#define BULLETMAX 100

struct BULLET
{
    Vector2 Pos; //��ġ
    Vector2 Dir; //����
    float   Speed; // �ӵ�


    float   Rot; //���� ȸ����
    bool    isFire; //�߻��ߴ°�?
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
    float rcSpeed; //rc�̵��ӵ�

    Object* ln; //�Ѿ��� �׷��� ����
    Circle* lnChild; //�Ѿ��� �����ϴ°�ü
    BULLET bl[BULLETMAX]; //�갡 �Ѿ�
public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����

    
    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

