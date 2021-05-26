#pragma once

enum RunPlayerState
{
    RPL_RUN,
    RPL_JUMP,
    RPL_SLIDE,
};

struct RunPlayer
{
    Image* Run;
    Image* Spin;
    Rect* Body;
    int    State;
    float  Gravity;
};


class Scene1 : public Scene
{
private:

    Image* Bg; //����
    Image* Floor;//�ٴ�
    RunPlayer Pl;

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����
    
    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

