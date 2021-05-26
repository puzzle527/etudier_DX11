#pragma once
class LightManager : public Singleton<LightManager>
{
private:
    struct Light
    {
        Vector2 ScreenPos;      //��ũ����ǥ
        float   Radius;         //������ũ��
        float   Padding = 0.0f; //���°�
        Color   LightColor;     //���� ��
    };
    ID3D11Buffer* LightBuffer;
public:
    Light               light;
    LightManager();
    ~LightManager();
    void                LightUpdate();
};

