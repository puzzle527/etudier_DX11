#pragma once
#define TRAILMAX 5

class Scene1 : public Scene
{
private:
    Image* bono1;
    Image* bono2;

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����
    
    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

