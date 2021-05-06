#include "stdafx.h"
#include "Scene2.h"
HRESULT Scene2::Init()
{
    pl = new Rect();
    pl->Init();
    pl->Scale = Vector2(100.0f, 100.0f);
    plPos = Vector2(400.0f, 300.0f);
    plRot = 0.0f;

    FrameCount = 0;
    Index = 0;
    return S_OK;
}

void Scene2::Release()
{
    delete pl;
}

void Scene2::Update()
{
    FrameCount++;
    //������Ʈ ���� ȣ���Ҷ�
    if (FrameCount % 50 == 0)
    {
        //Ʈ������ ����
        tr[Index].pos = plPos;
        tr[Index].rot = plRot;
        Index++;
        if (Index == TRAILMAX)
        {
            Index = 0;
        }
    }


   //�̵�
    //�¿�
    if (KEYMANAGER->KeyPress('A'))
    {
        plRot += DeltaTime;
    }
    else if (KEYMANAGER->KeyPress('D'))
    {
        plRot -= DeltaTime;
    }

    if (KEYMANAGER->KeyDown('R'))
    {
        plPos = tr[Index].pos;
        plRot = tr[Index].rot;
        for (int i = 0; i < TRAILMAX; i++)
        {
            tr[i].Reset();
        }
        Index = 0;
    }


    plPos +=
        pl->Right * 150.0f * DeltaTime;
}

void Scene2::LateUpdate()
{
    //���浹
    if (plPos.y > WINSIZEY - 50.0f ||
        plPos.y < 0.0f + 50.0f)
    {
        ReverseSeta(plRot);
    }

    if (plPos.x > WINSIZEX - 50.0f ||
        plPos.x < 0.0f + 50.0f)
    {
        ReverseSeta(plRot,false);
    }


}

void Scene2::Render()
{
    //�÷��̾� ���� ���� Ʈ���� �׷��ֱ�

    for (int i = 0; i < TRAILMAX; i++)
    {
        pl->Position = tr[i].pos;
        pl->Rotation.z = tr[i].rot;
        pl->WorldUpdate();
        pl->Render();
    }



    pl->Position = plPos;
    pl->Rotation.z = plRot;
    pl->WorldUpdate();
    pl->Render();
}
