#include "stdafx.h"
#include "Scene2.h"

void Scene2::Reset()
{
    pl[0].cc->Position = Vector2(200.0f, 600.0f);
    pl[1].cc->Position = Vector2(200.0f, 200.0f);
    pl[1].dir = Vector2(0.0f, 0.0f);
    pl[0].dir = Vector2(0.0f, 0.0f);
    pl[0].speed = PLMINSPEED;
    pl[1].speed = PLMINSPEED;
    ball->Position = Vector2(200.0f, 400.0f);
    ballSpeed = 0.0f;
    ballDir = Vector2(0.0f, 0.0f);
}

HRESULT Scene2::Init()
{
    // 0 위 1 아래

    pl[0].cc = new Circle();
    pl[0].cc->Init();
    
    pl[0].cc->Scale = Vector2(50.0f, 50.0f);
   
    pl[0].score = 0;
    pl[0].goal = new Rect();
    pl[0].goal->Init();
    pl[0].goal->Position = Vector2(200.0f, 800.0f);
    pl[0].goal->Scale = Vector2(100.0f, 40.0f);
    pl[0].goal->WorldUpdate();


    pl[1].cc = new Circle();
    pl[1].cc->Init();
   
    pl[1].cc->Scale = Vector2(50.0f, 50.0f);
    
    pl[1].score = 0;
    pl[1].goal = new Rect();
    pl[1].goal->Init();
    pl[1].goal->Position = Vector2(200.0f, 000.0f);
    pl[1].goal->Scale = Vector2(100.0f, 40.0f);
    pl[1].goal->WorldUpdate();

    center = new Line();
    center->Position = Vector2(0.0f, 400.0f);
    center->Scale = Vector2(400.0f, 1.0f);
    center->WorldUpdate();

    ball = new Circle();
    ball->Init();
    ball->Scale = Vector2(30.0f, 30.0f);
    
    Reset();


    return S_OK;
}

void Scene2::Release()
{
    delete pl[0].goal;
    delete pl[0].cc;

    delete pl[1].goal;
    delete pl[1].cc;
    delete center;

}

void Scene2::Update()
{

    ImGui::Text("1P: %d", pl[0].score);
    ImGui::Text("2P: %d", pl[1].score);

    //플레이어 입력
    //플레이어 방향,속력의 크기
    pl[0].dir = Vector2(0.0f, 0.0f);
    if (KEYMANAGER->KeyPress('W'))
    {
        pl[0].dir += UP;
    }
    else if (KEYMANAGER->KeyPress('S'))
    {
        pl[0].dir += DOWN;
    }
    if (KEYMANAGER->KeyPress('A'))
    {
        pl[0].dir += LEFT;
    }
    else if (KEYMANAGER->KeyPress('D'))
    {
        pl[0].dir += RIGHT;
    }

    //방향이 중립이 아닐때(키를 누른게 있을때)
    //실수 0 은 비교연산 가능
    if (pl[0].dir != Vector2(0.0f, 0.0f))
    {
        pl[0].speed += 100.0f * DeltaTime;
    }
    else
    {
        pl[0].speed -= 200.0f * DeltaTime;
    }
    Saturate(pl[0].speed, PLMINSPEED, PLMAXSPEED);

    D3DXVec2Normalize(&pl[0].dir, &pl[0].dir);
    //정해진 값으로 이동
    pl[0].cc->Position
        += pl[0].dir * pl[0].speed * DeltaTime;

    pl[0].cc->color =
        //     0.5~ 1.0    50 400    350   0 ~ 0.5
        Color((pl[0].speed -50.0f) /700.0f  + 0.5f,
            0.5f,
            0.5f, 1.0f);

    pl[1].dir = Vector2(0.0f, 0.0f);
    if (KEYMANAGER->KeyPress(VK_UP))
    {
        pl[1].dir += UP;
    }
    else if (KEYMANAGER->KeyPress(VK_DOWN))
    {
        pl[1].dir += DOWN;
    }
    if (KEYMANAGER->KeyPress(VK_LEFT))
    {
        pl[1].dir += LEFT;
    }
    else if (KEYMANAGER->KeyPress(VK_RIGHT))
    {
        pl[1].dir += RIGHT;
    }

    //방향이 중립이 아닐때(키를 누른게 있을때)
    //실수 0 은 비교연산 가능
    if (pl[1].dir != Vector2(0.0f, 0.0f))
    {
        pl[1].speed += 100.0f * DeltaTime;
    }
    else
    {
        pl[1].speed -= 200.0f * DeltaTime;
    }
    Saturate(pl[1].speed, PLMINSPEED, PLMAXSPEED);

    D3DXVec2Normalize(&pl[1].dir, &pl[1].dir);
    //정해진 값으로 이동
    pl[1].cc->Position
        += pl[1].dir * pl[1].speed * DeltaTime;

    pl[1].cc->color =
        Color(0.5f,
            0.5f,
            (pl[1].speed - 50.0f) / 700.0f + 0.5f, 1.0f);

    ballSpeed -= 100.0f * DeltaTime;
    Saturate(ballSpeed, 0.0f, 800.0f);
    ball->Position
        += ballDir * ballSpeed * DeltaTime;

    ball->color =
        Color(ballSpeed / 800.0f,
            ballSpeed / 800.0f,
            ballSpeed / 800.0f, 1.0f);



    pl[0].cc->WorldUpdate();
    pl[1].cc->WorldUpdate();
    ball->WorldUpdate();
}

void Scene2::LateUpdate()
{
    
    for (int i = 0; i < 2; i++)
    {
        //공 이랑 플레이어 충돌
        if (ColCir(pl[i].cc, ball))
        {
            Vector2 dir
                = ball->Position - pl[i].cc->Position;
            D3DXVec2Normalize(&dir, &dir);
            ballDir = dir;
            ballSpeed += pl[i].speed * 1.5f;
        }
        //공이랑 골대충돌
        if (ColRectCir(pl[i].goal, ball))
        {
            pl[(!i)].score++;
            Reset();
        }
    }



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
    }
}

void Scene2::Render()
{
    center->Render();
    pl[0].cc->Render();
    pl[1].cc->Render();
    pl[0].goal->Render();
    pl[1].goal->Render();
    ball->Render();
}

