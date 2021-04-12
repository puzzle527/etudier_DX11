#pragma once
class Scene2 : public Scene
{
private:
    Rect* Sun;
    Rect* Planet[5];

public:
    HRESULT Init() override;//초기화
    void Release() override;//해제


    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

