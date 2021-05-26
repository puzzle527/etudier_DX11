#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
    bono1 = new Image(_T("bono1.png"));
    bono1->Init();
    bono1->Scale = Vector2(100.0f, 100.0f);


    //1p
    pl[0].cc = new Circle();
    pl[0].cc->Init();
    pl[0].cc->Position = Vector2(50.0f, 50.0f);
    pl[0].cc->Scale = Vector2(100.0f, 100.0f);

    pl[0].cannon = new Line();
    pl[0].cannon->Init();
    pl[0].cannon->Scale = Vector2(100.0f, 100.0f);
    pl[0].cannon->P = &pl[0].cc->RT;
    pl[0].cannon->Rotation.z = PI * 0.25f;

    pl[0].fire = new Object();
    pl[0].fire->Init();
    pl[0].fire->Position = Vector2(100.0f, 0.0f);
    pl[0].fire->P = &pl[0].cannon->RT;

    pl[0].gauge = new Rect(Vector2(-0.5f,0.0f));
    pl[0].gauge->Init();
    pl[0].gauge->Position = Vector2(-50.0f, 150.0f);
    pl[0].gauge->Scale = Vector2(200.0f, 30.0f);
    pl[0].gauge->P = &pl[0].cc->RT;
    
    pl[0].power = 0.0f;

    //2p

    pl[1].cc = new Circle();
    pl[1].cc->Init();
    pl[1].cc->Position = Vector2(WINSIZEX - 50.0f, 50.0f);
    pl[1].cc->Scale = Vector2(100.0f, 100.0f);
    pl[1].cc->Rotation.y = PI;

    pl[1].cannon = new Line();
    pl[1].cannon->Init();
    pl[1].cannon->Scale = Vector2(100.0f, 100.0f);
    pl[1].cannon->P = &pl[1].cc->RT;
    pl[1].cannon->Rotation.z = PI * 0.25f;

    pl[1].fire = new Object();
    pl[1].fire->Init();
    pl[1].fire->Position = Vector2(100.0f, 0.0f);
    pl[1].fire->P = &pl[1].cannon->RT;

    pl[1].gauge = new Rect(Vector2(-0.5f, 0.0f));
    pl[1].gauge->Init();
    pl[1].gauge->Position = Vector2(-50.0f, 150.0f);
    pl[1].gauge->Scale = Vector2(200.0f, 30.0f);
    pl[1].gauge->P = &pl[1].cc->RT;

    pl[1].power = 0.0f;


    ball = new Circle();
    ball->Init();
    ball->Scale = Vector2(30.0f, 30.0f);

    turn = PLAYER1P;
    CurrentPl = &pl[0];
    ball->isActive = false;
    ballGravity = 0.0f;
    fireTime = 0.0f;

    return S_OK;
}

void Scene2::Release()
{
   

}

void Scene2::Update()
{
    // 0 , 2
    if (turn % 2 == 0)
    {
        if (KEYMANAGER->KeyPress(VK_LEFT))
        {
            CurrentPl->cc->Position +=
                LEFT * 150.0f * DeltaTime;
            /*pl[0].cc->Rotation.y -= DeltaTime;
            Saturate(pl[0].cc->Rotation.y
                , -PI, 0.0f);*/
        }
        if (KEYMANAGER->KeyPress(VK_RIGHT))
        {
            CurrentPl->cc->Position +=
                RIGHT * 150.0f * DeltaTime;
            /*pl[0].cc->Rotation.y += DeltaTime;
            Saturate(pl[0].cc->Rotation.y
                , -PI, 0.0f);*/
        }

        if (KEYMANAGER->KeyPress(VK_UP))
        {
            CurrentPl->cannon->Rotation.z
                += DeltaTime;
        }
        if (KEYMANAGER->KeyPress(VK_DOWN))
        {
            CurrentPl->cannon->Rotation.z
                -= DeltaTime;
        }
        if (KEYMANAGER->KeyPress(VK_SPACE))
        {
            CurrentPl->power += 200.0f * DeltaTime;
            if (CurrentPl->power > 200.0f)
            {
                CurrentPl->power = 0.0f;
            }
        }
        if (KEYMANAGER->KeyUp(VK_SPACE))
        {
            ball->isActive = true;
            ball->Position = 
                CurrentPl->fire->GetWorldPos();
            ballDir =
                CurrentPl->fire->GetWorldPos()
                - CurrentPl->cc->GetWorldPos();
            D3DXVec2Normalize(&ballDir, &ballDir);

            ballSpeed = CurrentPl->power*2.0f;
            turn++;
        }
    }
    //발사턴
    else
    {
        ball->Position +=
            ballDir * ballSpeed * DeltaTime;
        ball->Position +=
            DOWN * ballGravity * DeltaTime;
        ballGravity += 100.0f * DeltaTime;

        fireTime += DeltaTime;

        //터지기
        if (fireTime > 6.0f)
        {
            ball->color.r
                += DeltaTime * 0.5f;
            ball->Scale.x +=
                200.0f * DeltaTime;
            ball->Scale.y +=
                50.0f * DeltaTime;
            ballSpeed = 0.0f;
            ballGravity = 0.0f;
        }
        //턴넘기기
        if (fireTime > 7.0f)
        {
            ball->color.r = 0.5f;
            fireTime = 0.0f;
            ballGravity = 0.0f;
            ball->isActive = false;
            ball->Scale = Vector2(30.0f, 30.0f);

            turn = (turn + 1) % 4;
            //현재플레이어도 바꾸기
            CurrentPl = (turn) ? (&pl[1]) :
                (&pl[0]);
        }

        
    }
    
    if (KEYMANAGER->KeyPress('T'))
    {
        //pl[1].cc->Rotation.y += DeltaTime;
    }

    
    //ball->Position = pl[0].fire->Position;

    pl[0].gauge->Scale.x = pl[0].power;
    pl[0].cc->WorldUpdate();
    pl[0].cannon->WorldUpdate();
    pl[0].fire->WorldUpdate();
    pl[0].gauge->WorldUpdate();

    pl[1].gauge->Scale.x = pl[1].power;
    pl[1].cc->WorldUpdate();
    pl[1].cannon->WorldUpdate();
    pl[1].fire->WorldUpdate();
    pl[1].gauge->WorldUpdate();


    ball->WorldUpdate();
}

void Scene2::LateUpdate()
{

    //공이랑 벽충돌
    if (ball->Position.x < 15.0f ||
        ball->Position.x >WINSIZEX - 15.0f)
    {
        ballDir.x *= -1.0f;//좌우반전

    }
    if (ball->Position.y < 15.0f ||
        ball->Position.y >WINSIZEY - 15.0f)
    {
        ballDir.y *= -1.0f;//상하반전
        ballGravity *= -0.8f;
    }

    pl[0].cc->WorldUpdate();
    pl[0].cannon->WorldUpdate();
    pl[0].fire->WorldUpdate();
    pl[0].gauge->WorldUpdate();

    pl[1].cc->WorldUpdate();
    pl[1].cannon->WorldUpdate();
    pl[1].fire->WorldUpdate();
    pl[1].gauge->WorldUpdate();


    ball->WorldUpdate();
}

void Scene2::Render()
{
    //pl[0].cc->Render();
    bono1->Position = pl[0].cc->Position;
    bono1->WorldUpdate();
    bono1->Render();
    pl[0].cannon->Render();
    pl[0].fire->Render();
    pl[0].gauge->Render();
    pl[1].cc->Render();
    pl[1].cannon->Render();
    pl[1].fire->Render();
    pl[1].gauge->Render();
    ball->Render();
}

