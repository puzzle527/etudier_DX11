#pragma once
class LightManager : public Singleton<LightManager>
{
private:
    struct Light
    {
        Vector2 ScreenPos;      //스크린좌표
        float   Radius;         //반지름크기
        float   Padding = 0.0f; //남는값
        Color   LightColor;     //조명 색
    };
    ID3D11Buffer* LightBuffer;
public:
    Light               light;
    LightManager();
    ~LightManager();
    void                LightUpdate();
};

