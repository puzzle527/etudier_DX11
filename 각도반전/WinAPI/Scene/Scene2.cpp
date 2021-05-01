#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
    pl = new Rect();
    pl->Init();
    pl->Position = Vector2(400.0f, 300.0f);
    pl->Scale = Vector2(100.0f, 100.0f);

    cannon = new Line();
    cannon->Init();
    cannon->Position = Vector2(0.0f, 0.0f);
    cannon->Scale = Vector2(130.0f, 100.0f);
    cannon->P = &pl->RT;

    //�߻���ġ
    FirePos = new Object();
    FirePos->Init();
    FirePos->Position = Vector2(130.0f, 0.0f);
    //�θ������ ĳ������ �д�
    FirePos->P = &cannon->RT;

    for (int i = 0; i < BALLMAX; i++)
    {
        bl[i].cc = new Circle();
        bl[i].cc->Init();
        bl[i].cc->Scale = Vector2(30.0f, 30.0f);
        bl[i].cc->isActive = false;
        bl[i].cc->isAxis = true;
    }


    return S_OK;
}

void Scene2::Release()
{
    delete cannon;
    delete pl;
    delete FirePos;
    for (int i = 0; i < BALLMAX; i++)
    {
        delete bl[i].cc;
    }

}

void Scene2::Update()
{
    ImGui::ColorEdit4("plColor", pl->color);

    //ĳ���� �̵�
    if (KEYMANAGER->KeyPress('W'))
    {
        pl->Position += UP * 100.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('S'))
    {
        pl->Position += DOWN * 100.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('A'))
    {
        pl->Position += LEFT * 100.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('D'))
    {
        pl->Position += RIGHT * 100.0f * DeltaTime;
    }
    //ĳ�� ������
    cannon->Rotation = DirToRadian(g_Mouse - pl->Position);
   

    //�� �߻�
    if (KEYMANAGER->KeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < BALLMAX; i++)
        {
            if (!bl[i].cc->isActive)
            {
                bl[i].cc->isActive = true;
                bl[i].cc->Position
                    = FirePos->GetWorldPos();
                bl[i].cc->Rotation
                    = cannon->Rotation;

                break;
            }
        }
    }

    //�߻���Ѿ� �����̱�
    for (int i = 0; i < BALLMAX; i++)
    {
        if (bl[i].cc->isActive)
        {
            bl[i].cc->Position
                //      ����                 ũ��
                += bl[i].cc->Right * bl[i].speed * DeltaTime;
        }
    }


    pl->WorldUpdate();
    cannon->WorldUpdate();
    FirePos->WorldUpdate();
    for (int i = 0; i < BALLMAX; i++)
    {
        bl[i].cc->WorldUpdate();
    }
}

void Scene2::LateUpdate()
{
    //���尪 ������ �浹

   
    for (int i = 0; i < BALLMAX; i++)
    {
        if (!bl[i].cc->isActive) continue;
        //����, ������ ���̶� �ε�������
        if (bl[i].cc->Position.x < 15.0f||
            bl[i].cc->Position.x >WINSIZEX - 15.0f)
        {
            ReverseSeta(bl[i].cc->Rotation, false);
        }
        //����, �Ʒ��� ���̶� �ε�������
        if (bl[i].cc->Position.y < 15.0f ||
            bl[i].cc->Position.y >WINSIZEY - 15.0f)
        {
            ReverseSeta(bl[i].cc->Rotation, true);
        }

        //������ �ε�������
        for (int j = i + 1; j < BALLMAX; j++)
        {
            if (ColCir(bl[i].cc, bl[j].cc))
            {
                Vector2 Dir
                    = bl[i].cc->Position - bl[j].cc->Position;
                bl[i].cc->Rotation = DirToRadian(Dir);
                Dir *= -1.0f;
                bl[j].cc->Rotation = DirToRadian(Dir);
            }
        }
        //�������� ��ǥ�� ����
        Saturate(bl[i].cc->Position.x, 15.0f, WINSIZEX - 15.0f);
        Saturate(bl[i].cc->Position.y, 15.0f, WINSIZEY - 15.0f);

    }
    
    //���尪 �ٽ� ����
    for (int i = 0; i < BALLMAX; i++)
    {
        bl[i].cc->WorldUpdate();
    }
 
}

void Scene2::Render()
{
    pl->Render();
    cannon->Render();
    for (int i = 0; i < BALLMAX; i++)
    {
        bl[i].cc->Render();
    }
}
