#pragma once
class LoadingScene : public Scene
{
private:
    thread p1;  //�߰��Ҵ��� ������
    Rect* Bar; //�ε�������

public:
    LoadingScene();
    ~LoadingScene();
    HRESULT Init() override;
    void Release() override;

    void Update() override;
    void LateUpdate() override;
    void Render() override;
    void TextRender() override;

    //thiscall X
    static void CreateScene();
};

