#pragma once

class Scene2 : public Scene
{
private:
    Image* Pl;
public:
    Scene2();
    ~Scene2();
    HRESULT Init() override;
    void Release() override;

    void Update() override;
    void LateUpdate() override;
    void Render() override;
};

