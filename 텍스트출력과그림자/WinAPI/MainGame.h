#pragma once
class MainGame
{
private:
    
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
    void TextRender();//�׸���
};

