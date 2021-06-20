#pragma once
//∞‘¿” æ¿
class Scene2 : public Scene
{
private:
    class Player* Pl;
    class Monster* Mon;
    class IsoTileMap* Tm;

public:
    Scene2();
    ~Scene2();
    HRESULT Init() override;
    void Release() override;

    void Update() override;
    void LateUpdate() override;
    void Render() override;
    void TextRender() override;
};

