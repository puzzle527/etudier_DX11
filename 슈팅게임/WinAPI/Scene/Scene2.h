#pragma once

struct ShootPlayer
{
    Image*  Move;
    Image*  Boost;
    Circle* Body;
    int     State;
    float   Handle = 0.0f; //�� -,�� +,�߸� 0
};

class Scene2 : public Scene
{
private:
    Image* Bg;
    ShootPlayer Pl;

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����


    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

