#pragma once
class Scene3 : public Scene
{
private:
    class IsoTileMap* Tm;

    int     State;      //Ÿ�� ����
    Int2    TileSize;   //Ÿ�� ����
    UINT    ImgIdx;     //���° �̹���?
    Int2    Frame;      //�ٲ��� ������ǥ
public:
    Scene3();
    ~Scene3();
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����

    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
    void TextRender() override;

    //�Լ��� ���� ȣ��

    //�������� ��ư
    void ResizeButton();
    //Ÿ�ϸ� �̹��� ��ư
    void TileImgButton();
    //Ÿ�ϸ� �귯��
    void TileBrush();

};



