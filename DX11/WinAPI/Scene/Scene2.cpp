#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
    Sun = new Rect();
    Sun->Init();
    Sun->Scale = Vector2(100.0f,100.0f);
    Sun->Position = Vector2(400.0f,300.0f);
    Sun->isAxis = true;


    for(int i = 0; i < 5; i++)
    {
        Planet[i] = new Rect();
        Planet[i]->Init();
        Planet[i]->Scale = Vector2(50.0f, 50.0f);
        Planet[i]->Position = Vector2(100.0f*(i+1), 0.0f);
        Planet[i]->P = &Sun->RT;
        Planet[i]->isAxis = true;
    }


    return S_OK;
}

void Scene2::Release()
{
    delete Sun;
    for(int i = 0; i < 5; i++)
    {
        delete Planet[i];
    }
}

void Scene2::Update()
{
    //Sun->Rotation +=0.05f;

    if(KEYMANAGER->KeyPress('A'))
    {
        Sun->Rotation -= 0.1f;
    }
    if(KEYMANAGER->KeyPress('D'))
    {
        Sun->Rotation += 0.1f;
    }

    for(int i = 0; i < 5; i++)
    {
        Planet[i]->Rotation
            -= (i + 1) * 0.05f;
        Planet[i]->Rotation2
            += (i+1) * 0.05f;
    }
}

void Scene2::LateUpdate()
{
    Sun->WorldUpdate();
    for(int i = 0; i < 5; i++)
    {
        Planet[i]->WorldUpdate();
    }
}

void Scene2::Render()
{
    Sun->Render();
    for(int i = 0; i < 5; i++)
    {
        Planet[i]->Render();
    }
}
