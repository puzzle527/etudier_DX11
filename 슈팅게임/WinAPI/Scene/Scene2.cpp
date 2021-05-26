#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
  
    Bg = new Image(_T("bg.png"),
        Vector2(-0.5f,-0.5f));
    Bg->Init();
    Bg->Scale = Vector2(448.0f, 4288.0f);
    Bg->WorldUpdate();
    Bg->ChangeAddress(_WRAP);

    Pl.Body = new Circle(36, Vector2(0.0f, 0.5f),false);
    Pl.Body->Init();
    Pl.Body->Position = Vector2(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
    Pl.Body->Scale = Vector2(30.0f, 30.0f);
    Pl.Body->color = Color(1.0f, 0.0f, 0.0f, 0.5f);

    Pl.Move = new Image(_T("LeftRight.png"), Vector2(0.0f, 0.5f));
    Pl.Move->Init();
    Pl.Move->MaxFrame.x = 7;
    Pl.Move->Position.y += 20.0f;
    Pl.Move->Scale = Vector2(64.0f, 80.0f);
    Pl.Move->P = &Pl.Body->RT;
    
    
    Pl.Boost = new Image(_T("Start.png"), Vector2(0.0f, 0.5f));
    Pl.Boost->Init();
    Pl.Boost->MaxFrame.x = 11;
    Pl.Boost->Scale = Vector2(64.0f, 240.0f);
    Pl.Boost->P = &Pl.Body->RT;
    Pl.Boost->Position.y += 20.0f;
    Pl.Boost->isActive = false;
    Pl.Boost->ChangeAnim(_LOOP, 0.1f);

    return S_OK;
}

void Scene2::Release()
{
   
}

void Scene2::Update()
{
    //   1초에 4288.0f 이동
    //   1초에 200.0f 이동
    Bg->UV.y -= DeltaTime * 200.0f / Bg->Scale.y;
    Bg->UV.w -= DeltaTime * 200.0f / Bg->Scale.y;

    if (KEYMANAGER->KeyPress(VK_LEFT))
    {
        Pl.Body->Position
            += LEFT * 100.0f * DeltaTime;
        Pl.Handle -= DeltaTime * 2.0f;
    }
    else if (KEYMANAGER->KeyPress(VK_RIGHT))
    {
        Pl.Body->Position
            += RIGHT * 100.0f * DeltaTime;
        Pl.Handle += DeltaTime * 2.0f;
    }
    //핸들을 놨을때
    else
    {
        if (Pl.Handle > DeltaTime * 2.0f)
        {
            Pl.Handle -= DeltaTime * 2.0f;
        }
        else if (Pl.Handle < -DeltaTime * 2.0f)
        {
            Pl.Handle += DeltaTime * 2.0f;
        }
        else
        {
            Pl.Handle = 0.0f;
        }
    }
    Saturate(Pl.Handle, -1.0f, 1.0f);
    //-1 ~ 1 +1 * 3
    //-> 0 ~ 6
    Pl.Move->Frame.x
        = (Pl.Handle + 1.0f) * 3.0f;


    if (KEYMANAGER->KeyPress(VK_UP))
    {
        Pl.Body->Position
            += UP * 100.0f * DeltaTime;
    }
    else if (KEYMANAGER->KeyPress(VK_DOWN))
    {
        Pl.Body->Position
            += DOWN * 100.0f * DeltaTime;
    }










    if (KEYMANAGER->KeyDown('1'))
    {
        Pl.Boost->isActive = true;
        Pl.Move->isActive = false;
    }
    if (KEYMANAGER->KeyDown('2'))
    {
        Pl.Boost->isActive = false;
        Pl.Move->isActive = true;
    }


    Pl.Body->WorldUpdate();
    Pl.Move->WorldUpdate();
    Pl.Boost->WorldUpdate();
}

void Scene2::LateUpdate()
{

    Pl.Body->WorldUpdate();
    Pl.Move->WorldUpdate();
    Pl.Boost->WorldUpdate();
}

void Scene2::Render()
{
    Bg->Render();
    Pl.Move->Render();
    Pl.Boost->Render();
    Pl.Body->Render();
}

