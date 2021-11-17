#pragma once
//�ʿ����� ��
class Scene1 : public Scene
{
private:
    class TileMap* Tm;
   
    int     State;      //Ÿ�� ����
    Int2    TileSize;   //Ÿ�� ����
    UINT    ImgIdx;     //���° �̹���?
    Int2    Frame;      //�ٲ��� ������ǥ
public:
    Scene1();
    ~Scene1();
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����
    
    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���

    //�Լ��� ���� ȣ��
    
    //�������� ��ư
    void ResizeButton();
    //Ÿ�ϸ� �̹��� ��ư
    void TileImgButton();
    //Ÿ�ϸ� �귯��
    void TileBrush();

};

