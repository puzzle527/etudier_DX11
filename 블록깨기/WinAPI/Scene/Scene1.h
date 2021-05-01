#pragma once
#define ROWCOUNT 20
#define COLCOUNT 3
#define BLOCKMAX ROWCOUNT*COLCOUNT

struct BLOCK
{
    Rect* rc;
    int   life;
};

class Scene1 : public Scene
{
private:
    BLOCK bl[BLOCKMAX];
    Rect* pl;

    Circle* ball;
    Vector2 ballDir; //��¹���
    float   ballSpeed = 200.0f; //�ӷ�
    float   cor;
public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����

    
    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

