#include "stdafx.h"
#include "Scene1.h"

//���� ���׸���
//ȸ���̵�ũ�� ��ȯ ����

HRESULT Scene1::Init()
{
    rc = new Rect();
    rc->Init();
    rc->Position = Vector2(400.0f, 300.0f);
    rc->Scale = Vector2(100.0f, 100.0f);

    for (int i = 0; i < TRAILMAX; i++)
    {
        trail[i] = new Rect();
        trail[i]->Init();
        trail[i]->Scale = Vector2(100.0f, 100.0f);
    }
    


    return S_OK;
}

void Scene1::Release()
{
    delete rc;
    for (int i = 0; i < TRAILMAX; i++)
    {
        delete trail[i];
    }
}

void Scene1::Update()
{
    //�����ֱ⸶�� trail ��ġ�� ����
    FrameCount++;
    //0.5�ʸ���
    if (FrameCount % 100 == 0)
    {
        trail[UpdateIndex]->Position = rc->Position;
        trail[UpdateIndex]->Rotation = rc->Rotation;
        trail[UpdateIndex]->WorldUpdate();
        //�������ʷ� ����
        UpdateIndex++;
        if (UpdateIndex == TRAILMAX)
        {
            UpdateIndex = 0;
        }
    }


    if (KEYMANAGER->KeyPress(VK_LEFT))
    {
        //�ʴ� 1radian
        //�ʴ� �?
        rc->Rotation += DeltaTime;
    }
    if (KEYMANAGER->KeyPress(VK_RIGHT))
    {
        rc->Rotation -= DeltaTime;
    }
    if (KEYMANAGER->KeyDown('E'))
    {
        rc->Position = trail[UpdateIndex]->Position;
        rc->Rotation = trail[UpdateIndex]->Rotation;
        for (int i = 0; i < TRAILMAX; i++)
        {
            trail[i]->Position.x = FLT_MAX;
            trail[i]->Position.y = FLT_MAX;
            trail[i]->WorldUpdate();
        }
        UpdateIndex = 0;
    }

   
    rc->Position +=
        rc->Right * 100.0f * DeltaTime;
    rc->WorldUpdate();
}

void Scene1::LateUpdate()
{
    //���̶� ���浹
    if (rc->Position.x < 50.0f ||
        rc->Position.x >WINSIZEX - 50.0f)
    {
        ReverseSeta(rc->Rotation, false);
    }
    if (rc->Position.y < 50.0f ||
        rc->Position.y >WINSIZEY - 50.0f)
    {
        ReverseSeta(rc->Rotation);
    }
    rc->WorldUpdate();
}

void Scene1::Render()
{
    
    for (int i = 0; i < TRAILMAX; i++)
    {
        trail[i]->Render();
    }
    rc->Render();
}
