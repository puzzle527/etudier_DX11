#pragma once
#define BALLMAX 40

//�ӵ�: ����� ũ��   (����)
//�ӷ�: ũ��   �ڵ�������� km/1h (��Į��)

struct Ball
{
    Circle* cc;

    Vector2 dir; //��¹���
    float   speed = 200.0f; //�ӷ�
    

    Vector2 velocity; //�ӵ�
    float   gravity;  //�߷�


    // �ӵ� = ����* �ӷ�
    //  v   =  v * k
};

class Scene2 : public Scene
{
private:
    Ball bl[BALLMAX];
    Rect* pl;
    Line* cannon;
    Object* FirePos;//�߻���ġ
    float   cor = 1.0f; //�ݹ߰��

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����


    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

