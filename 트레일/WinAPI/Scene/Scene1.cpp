#include "stdafx.h"
#include "Scene1.h"

//과제 원그리기
//회전이동크기 변환 구현

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
    //일정주기마다 trail 위치값 갱신
    FrameCount++;
    //0.5초마다
    if (FrameCount % 100 == 0)
    {
        trail[UpdateIndex]->Position = rc->Position;
        trail[UpdateIndex]->Rotation = rc->Rotation;
        trail[UpdateIndex]->WorldUpdate();
        //다음차례로 갱신
        UpdateIndex++;
        if (UpdateIndex == TRAILMAX)
        {
            UpdateIndex = 0;
        }
    }


    if (KEYMANAGER->KeyPress(VK_LEFT))
    {
        //초당 1radian
        //초당 몇도?
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
    //공이랑 벽충돌
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
