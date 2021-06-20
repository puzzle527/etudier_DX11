#pragma once
class LoadingScene : public Scene
{
private:
    thread p1;  //추가할당할 스레드
    Rect* Bar; //로딩게이지

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

