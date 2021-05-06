#pragma once
#define TRAILMAX 5

class Scene1 : public Scene
{
private:
    Rect* rc;

    Rect* trail[TRAILMAX];

    int   FrameCount = 0;
    //������ �ε���
    int   UpdateIndex = 0;

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����
    
    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

