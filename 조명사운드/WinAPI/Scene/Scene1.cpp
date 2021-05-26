#include "stdafx.h"
#include "Scene1.h"

//���� ���׸���
//ȸ���̵�ũ�� ��ȯ ����

Scene1::Scene1()
{
    //������ �ٲ��� ������
    Bg = new Image(_T("back.png"));
    Bg->Init();
    Bg->Scale = Vector2(800.0f, 600.0f);
    Bg->Position = Vector2(400.0f, 300.0f);
    Bg->WorldUpdate();
    Bg->ChangeAddress(_WRAP);

    Floor = new Image(_T("floor.bmp"), Vector2(-0.5f, -0.5f));
    Floor->Init();
    Floor->Scale = Vector2(800.0f, 96.0f);
    Floor->WorldUpdate();
    Floor->ChangeAddress(_WRAP);

    Pl.Body = new Rect(Vector2(0.0f, -0.5f), false);
    Pl.Body->Init();

    Pl.Spin = new Image(_T("spin.bmp"), Vector2(0.0f, -0.5f));
    Pl.Spin->Init();
    Pl.Spin->Scale = Vector2(96.0f, 96.0f);
    Pl.Spin->MaxFrame.x = 5;//����5���� �̹���
    Pl.Spin->P = &Pl.Body->RT;

    //48x60
    Pl.Run = new Image(_T("run.bmp"), Vector2(0.0f, -0.5f));
    Pl.Run->Init();
    Pl.Run->Scale = Vector2(96.0f, 120.0f);
    Pl.Run->MaxFrame.x = 4;//����5���� �̹���
    Pl.Run->P = &Pl.Body->RT;

}

Scene1::~Scene1()
{
    delete Bg;
    delete Floor;
    delete Pl.Body;
    delete Pl.Spin;
    delete Pl.Run;
}

HRESULT Scene1::Init()
{ 
    
    //79x48 ������ �ٴ� �׸���

    
    //158�������϶� ��� ��������?
    Floor->UV.x = 0.0f;
    Floor->UV.z = 800.0f / 158.0f;
   
    Pl.Body->Position = Vector2(100.0f, 96.0f);

    //48x48
   
    //�⺻�� ������
    Pl.State = RPL_RUN;
    Pl.Gravity = 0.0f;
    Pl.Body->Scale = Pl.Run->Scale;
    Pl.Body->Scale.x -= 20.0f;
    Pl.Spin->isActive = false;
    Pl.Run->isActive = true;
    Pl.Run->ChangeAnim(_LOOP, 0.1f);
   
    return S_OK;
}

void Scene1::Release()
{
}

void Scene1::Update()
{
    if (KEYMANAGER->KeyDown('1'))
    {
        SCENEMANAGER->ChangeScene("sc2")
            ->Init();
        Release();
    }



    //������ �������� �ʴ� 30�ȼ� �̵���Ű��
    Bg->UV.x += DeltaTime / (800.0f / 30.0f);
    Bg->UV.z += DeltaTime / (800.0f / 30.0f);

    //�ٴ��� �������� �ʴ� 100�ȼ� �̵���Ű��

    Floor->UV.x += DeltaTime / (158.0f / 100.0f);
    Floor->UV.z += DeltaTime / (158.0f / 100.0f);

    //�� ���¿����� Ű�Է� ���
    if (Pl.State == RPL_RUN)
    {
        //�����̵�
        if (KEYMANAGER->KeyDown(VK_DOWN))
        {
            Pl.State = RPL_SLIDE;
            Pl.Body->Scale = Pl.Spin->Scale;
            Pl.Body->Scale.x -= 20.0f;
            Pl.Spin->isActive = true;
            Pl.Run->isActive = false;
            Pl.Spin->ChangeAnim(_ONCE, 0.1f);
        }

        //����
        if (KEYMANAGER->KeyDown(VK_SPACE))
        {
            Pl.State = RPL_JUMP;
            Pl.Body->Scale = Pl.Spin->Scale;
            Pl.Body->Scale.x -= 20.0f;
            Pl.Spin->isActive = true;
            Pl.Run->isActive = false;
            Pl.Spin->ChangeAnim(_ONCE, 0.1f);
            //�ڱ�ġ�� �� ũ��
            Pl.Gravity = -500.0f;
        }
        
    }
    else if (Pl.State == RPL_SLIDE)
    {
        //������ �ٲ� �غ�
        if (KEYMANAGER->KeyUp(VK_DOWN))
        {
            Pl.Spin->ChangeAnim(_MIRRORONCE, 0.1f);
            
        }
        if (Pl.Spin->GetAnimState() == _MIRRORONCE
            and Pl.Spin->Frame.x == 0)
        {
            Pl.State = RPL_RUN;
            Pl.Body->Scale = Pl.Run->Scale;
            Pl.Body->Scale.x -= 20.0f;
            Pl.Spin->isActive = false;
            Pl.Run->isActive = true;
            Pl.Run->ChangeAnim(_LOOP, 0.1f);
        }

    }
    //�������� �϶�
    else
    { 
        //�߷��� ���� �ֱ�
        Pl.Body->Position
            += DOWN * Pl.Gravity * DeltaTime;
        Pl.Gravity += 400.0f * DeltaTime;
        
        //������ �ٲ� �غ�
        if (Pl.Body->Position.y < 96.0f)
        {
            Pl.Body->Position.y = 96.0f;
            Pl.State = RPL_RUN;
            Pl.Body->Scale = Pl.Run->Scale;
            Pl.Body->Scale.x -= 20.0f;
            Pl.Spin->isActive = false;
            Pl.Run->isActive = true;
            Pl.Run->ChangeAnim(_LOOP, 0.1f);
        }

    }

    Pl.Spin->WorldUpdate();
    Pl.Run->WorldUpdate();
    Pl.Body->WorldUpdate();
}

void Scene1::LateUpdate()
{
    //������ �ٲ� �����ǰ����ɷ�
    //�浹����



    Pl.Spin->WorldUpdate();
    Pl.Run->WorldUpdate();
    Pl.Body->WorldUpdate();
}

void Scene1::Render()
{
    Bg->Render();
    Floor->Render();
   

    Pl.Spin->Render();
    Pl.Run->Render();
    Pl.Body->Render();
}
