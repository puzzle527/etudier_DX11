#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
    Run = new Image(_T("·Ï¸Ç.png"));
    Run->Init();
    Run->Position = Vector2(400.0f, 300.0f);
    Run->Scale = Vector2(300.0f, 300.0f);
    Run->UV.x = 0.0f / 10.0f;
    Run->UV.z = 1.0f / 10.0f;
    Run->UV.y = 0.0f / 2.0f;
    Run->UV.w = 1.0f / 2.0f;
    Run->ChangeAddress(_WRAP);

    Bg = new Image(_T("bono/bono.jpg"));
    Bg->Init();
    Bg->Position = Vector2(400.0f, 300.0f);
    Bg->Scale = Vector2(800.0f, 600.0f);
    Bg->UV.x = -5.0f;
    Bg->UV.z = 5.0f;
    Bg->UV.y = -5.0f;
    Bg->UV.w = 5.0f;

    return S_OK;
}

void Scene2::Release()
{
    delete Run;

}

void Scene2::Update()
{
    if (KEYMANAGER->KeyDown('1'))
    {
        Run->ChangeFilter(_POINT);
    }
    if (KEYMANAGER->KeyDown('2'))
    {
        Run->ChangeFilter(_LINEAR);
    }
    if (KEYMANAGER->KeyDown('3'))
    {
        Bg->ChangeAddress(_CLAMP);
    }
    if (KEYMANAGER->KeyDown('4'))
    {
        Bg->ChangeAddress(_WRAP);
    }
    if (KEYMANAGER->KeyDown('5'))
    {
        Bg->ChangeAddress(_MIRROR);
    }
    if (KEYMANAGER->KeyDown(VK_SPACE))
    {
        Run->UV.x += 1.0f / 10.0f;
        Run->UV.z += 1.0f / 10.0f;
    }


    Run->WorldUpdate();
    Bg->WorldUpdate();
}

void Scene2::LateUpdate()
{

}

void Scene2::Render()
{
    Bg->Render();
    Run->Render();
}

