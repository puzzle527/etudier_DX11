#pragma once
#define TRAILMAX 5

class Scene1 : public Scene
{
private:
    Image* bono1;
    Rect*  bono1rc;     //�浹�� ������Ʈ


    Image* bono2;
    Circle* bono2cc;    //�浹�� ������Ʈ

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����
    
    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

