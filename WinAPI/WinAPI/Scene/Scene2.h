#pragma once
class Scene2 : public Scene
{
private:
    //Circle* cc;
	Star* st;

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����


    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

