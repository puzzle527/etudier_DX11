#pragma once
class MainGame
{
private:
   Scene* pCurrentScene = nullptr;
   //����ġ �� ��
   Scene* sc1;
   Scene* sc2;
   bool   isVsync; //��������ȭ �Ұ���
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

