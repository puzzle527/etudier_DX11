#pragma once
#define DDMAX 50
#define BGMAX 30

class DD
{
public:
    Circle* cc;
    float speed;
    Vector2 dir;
    float lifeTime;
    void Reset(Vector2 Pos);

};


class Scene1 : public Scene
{
    //friend class DD;
private:
    Rect* pl;       //�갡 ������ �÷��̾�
    Circle* child[2];

    //������ ��
    float   Distance; //�־��� �Ÿ�
    float   Radius;   //������
    float   Speed;    //ȸ���ӵ�


    DD    dd[DDMAX];//������ DD

    Star* bg[BGMAX]; //���

    //�ð�ũ�Ⱚ
    float timeScale = 1.0f;
    int   count = 0;

public:
    HRESULT Init() override;
    void Release() override;

    void Update() override;
    void LateUpdate() override;
    void Render() override;
};

