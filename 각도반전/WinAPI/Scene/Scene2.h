#pragma once
#define BALLMAX 40
struct Ball
{
    Circle* cc;
    //Vector2 dir;
    float   speed = 100.0f;

};

class Scene2 : public Scene
{
private:
    Ball bl[BALLMAX];
    Rect* pl;
    Line* cannon;
    Object* FirePos;//�߻���ġ

public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����


    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

