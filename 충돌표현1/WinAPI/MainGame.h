#pragma once
class MainGame
{
private:
    //���� ��
    Scene* CurrentScene = nullptr;
   
    //��ü�� ��
    Scene* sc1;
    Scene* sc2;

public:
    MainGame();//����
    ~MainGame();//�Ҹ�

    HRESULT Init();//�ʱ�ȭ
    void Release();//����

    //����
    void Update();//����
    void LateUpdate();//��������
    void Render();//�׸���
};

