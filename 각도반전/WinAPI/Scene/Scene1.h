#pragma once
#define DROPMAX 30
#define BGMAX 30

struct DROP
{
    Circle* cc;
    float   Speed;
    //float   Seta;
    Vector2 Dir;


    //�������ų� ���������� ��ġ,���ǵ� ���ġ
    void Reset(Vector2 pos) //�����̵Ǵ� ��ġ
    {
        //0~360���� ����
        float Seta = RndFloat(0.0f, 2.0f * PI);
        //���̰��� ���� �־��� ��ǥ
        cc->Position = pos + 
            Vector2(cosf(Seta), sinf(Seta)) * 
            (500.0f +RndFloat(50.0f,200.0f));
        //���̰� �����߻�
        Seta += RndFloat(-0.5f,0.5f);
        //�ݴ� ���̰����� ���� ���ϱ�
        Dir = -Vector2(cosf(Seta), sinf(Seta));
        Speed = RndFloat(100.0f, 400.0f);
        cc->color = Color(RndFloat(), RndFloat(), RndFloat(), 1.0f);
    }
};

class Scene1 : public Scene
{
private:
    Rect* player;
    DROP  dr[DROPMAX];
    float timeScale = 1.0f;
    Star* bg[BGMAX]; //���
    int   Score = 0;
public:
    HRESULT Init() override;//�ʱ�ȭ
    void Release() override;//����

    
    void Update() override;//����
    void LateUpdate() override;//��������
    void Render() override;//�׸���
};

