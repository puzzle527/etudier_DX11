#pragma once
class Scene2 : public Scene
{
private:
    Rect* cc;

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����


    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

