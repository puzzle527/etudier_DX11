#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
    cc = new Rect();
    cc->Init();
    cc->Scale = Vector2(200.0f,200.0f);
    cc->Position = Vector2(400.0f,300.0f);
    cc->isAxis = true;

    return S_OK;
}

void Scene2::Release()
{
    delete cc;
}

void Scene2::Update()
{
    //Sun->Rotation +=0.05f;

    if (KEYMANAGER->KeyPress(VK_LBUTTON)
        && g_Mouse.x >= cc->Position.x - cc->Scale.x / 2 && g_Mouse.x <= cc->Position.x + cc->Scale.x / 2
        && g_Mouse.y >= cc->Position.y - cc->Scale.y / 2 && g_Mouse.y <= cc->Position.y + cc->Scale.y / 2)
    {
        cc->Position += g_Mouse - g_Last_Mouse;
    }

    if(KEYMANAGER->KeyPress('W'))
    {
        cc->Position += Vector2(0, 1) *150.0f *DeltaTime;
    }
    if(KEYMANAGER->KeyPress('S'))
    {
        cc->Position += Vector2(0, -1) *150.0f *DeltaTime;
    }
    cc->Position.y
        = Saturate(cc->Position.y,100.0f, 500.0f);
    /*if(cc->Position.y > 500)
    {
        cc->Position.y = 500.0f;
    }
    if(cc->Position.y < 100)
    {
        cc->Position.y = 100.0f;
    }*/
}

void Scene2::LateUpdate()
{
    g_Last_Mouse = g_Mouse;
    cc->WorldUpdate();
}

void Scene2::Render()
{
    cc->Render();
}
