#pragma once
#define TRAILMAX 10

struct Trail
{
    Vector2 pos;
    float   rot;
    Trail()
    {
        pos = Vector2(FLT_MAX, FLT_MAX);
    }
    void Reset()
    {
        pos = Vector2(FLT_MAX, FLT_MAX);
        rot = 0.0f;
    }
};

class Scene2 : public Scene
{
    Rect*   pl;
    Vector2  plPos;
    float    plRot;


    Trail   tr[TRAILMAX];
    int     Index; //갱신할 인덱스

    int     FrameCount;

public:
    HRESULT Init() override;
    void Release() override;

    void Update() override;
    void LateUpdate() override;
    void Render() override;
};

