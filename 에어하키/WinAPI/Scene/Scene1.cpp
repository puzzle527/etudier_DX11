#include "stdafx.h"
#include "Scene1.h"

HRESULT Scene1::Init()
{
    //0 좌 1 우

    turn = PLAYER1;

    //기준
    pl[0].body = new Rect();
    pl[0].body->Init();
    pl[0].body->Scale= Vector2(100.0f, 100.0f);
    pl[0].body->Position= Vector2(50.0f, 50.0f);

    pl[0].angle = PI * 0.25f;

    pl[0].cannon = new Line();
    pl[0].cannon->Init();
    pl[0].cannon->Scale = Vector2(100.0f, 1.0f);
    pl[0].cannon->Rotation.z = pl[0].angle;
    pl[0].cannon->P = &pl[0].body->RT;

    pl[0].fire = new Object();
    pl[0].fire->Init();
    pl[0].fire->Position = Vector2(100.0f, 0.0f);
    pl[0].fire->P = &pl[0].cannon->RT;

    pl[0].gauge = new Rect(Vector2(-0.5f,0.0f));
    pl[0].gauge->Init();
    pl[0].gauge->Scale = Vector2(150.0f, 20.0f);
    pl[0].gauge->Position = Vector2(-50.0f, 200.0f);
    pl[0].gauge->P = &pl[0].body->RT;


    pl[1].body = new Rect();
    pl[1].body->Init();
    pl[1].body->Scale = Vector2(100.0f, 100.0f);
    pl[1].body->Position = Vector2(WINSIZEX - 50.0f, 50.0f);

    pl[1].body->Rotation.y = PI;

    pl[1].angle = PI * 0.25f;

    pl[1].cannon = new Line();
    pl[1].cannon->Init();
    pl[1].cannon->Scale = Vector2(100.0f, 1.0f);
    pl[1].cannon->Rotation.z = pl[1].angle;
    pl[1].cannon->P = &pl[1].body->RT;

    pl[1].fire = new Object();
    pl[1].fire->Init();
    pl[1].fire->Position = Vector2(100.0f, 0.0f);
    pl[1].fire->P = &pl[1].cannon->RT;

    pl[1].gauge = new Rect(Vector2(-0.5f, 0.0f));
    pl[1].gauge->Init();
    pl[1].gauge->Scale = Vector2(150.0f, 20.0f);
    pl[1].gauge->Position = Vector2(-50.0f, 200.0f);
    pl[1].gauge->P = &pl[1].body->RT;

    Control = &pl[0];



    //pl[1].body = new Rect();
   
    

    return S_OK;
}

void Scene1::Release()
{
    
}

void Scene1::Update()
{
    ImGui::SliderAngle("yAxisRot",
        &pl[1].body->Rotation.y);

    if (turn % 2 == 0)
    {
        if (KEYMANAGER->KeyPress(VK_LEFT))
        {
            Control->body->Position
                += LEFT * 100.0f * DeltaTime;
        }
        else if (KEYMANAGER->KeyPress(VK_RIGHT))
        {
            Control->body->Position
                += RIGHT * 100.0f * DeltaTime;
        }
        if (KEYMANAGER->KeyPress(VK_UP))
        {
            Control->angle += DeltaTime;
        }
        else if (KEYMANAGER->KeyPress(VK_DOWN))
        {
            Control->angle -= DeltaTime;
        }
        if (KEYMANAGER->KeyPress(VK_SPACE))
        {
            Control->power += 150.0f * DeltaTime;
            if (Control->power > 150.0f)
            {
                Control->power = 0.0f;
            }
        }
        if (KEYMANAGER->KeyUp(VK_SPACE))
        {
            turn++;
        }
    }
    //발사중
    else
    {
        //1->2
        //3->0
        turn = (turn + 1) % 4;
        Control = &pl[turn/2];
    }

    pl[0].gauge->Scale.x = pl[0].power;
    pl[0].cannon->Rotation.z = pl[0].angle;
    pl[0].body->WorldUpdate();
    pl[0].cannon->WorldUpdate();
    pl[0].fire->WorldUpdate();
    pl[0].gauge->WorldUpdate();

    pl[1].gauge->Scale.x = pl[1].power;
    pl[1].cannon->Rotation.z = pl[1].angle;
    pl[1].body->WorldUpdate();
    pl[1].cannon->WorldUpdate();
    pl[1].fire->WorldUpdate();
    pl[1].gauge->WorldUpdate();

}

void Scene1::LateUpdate()
{
   
   
}

void Scene1::Render()
{
   

    pl[0].body->Render();
    pl[0].cannon->Render();
    pl[0].gauge->Render();

    pl[1].body->Render();
    pl[1].cannon->Render();
    pl[1].gauge->Render();
}
