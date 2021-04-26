#pragma once
class Scene2 : public Scene
{
private:

    Rect* rc1;       
    Rect* rc2;  


public:
    HRESULT Init() override;
    void Release() override;

    void Update() override;
    void LateUpdate() override;
    void Render() override;
};

