#pragma once

class Scene2 : public Scene
{
private:
    //������
    Image* Puzzle[3][3];
    //����ִ� ��ǥ
    Int2   Null;


public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����


    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

