#pragma once
#define TRAILMAX 5

class Scene1 : public Scene
{
private:
    Rect* rc;

    Rect* trail[TRAILMAX];

    int   FrameCount = 0;
    //갱신할 인덱스
    int   UpdateIndex = 0;

public:
    HRESULT Init() override;//초기화
    void Release() override;//해제
    
    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

