#include "stdafx.h"
#include "Scene1.h"

//과제 원그리기
//회전이동크기 변환 구현

HRESULT Scene1::Init()
{
    Vector2 LT;
    LT.x = WINSIZEX / ROWCOUNT * 0.5f;
    LT.y = WINSIZEY - WINSIZEY *0.2f / COLCOUNT * 0.5f;

    for (int i = 0; i < COLCOUNT; i++)
    {
        for (int j = 0; j < ROWCOUNT; j++)
        {
            int idx = i * ROWCOUNT + j;
            bl[idx].rc = new Rect();
            bl[idx].rc->Init();
            bl[idx].rc->Scale =
                Vector2(WINSIZEX / ROWCOUNT,
                    WINSIZEY * 0.2f / COLCOUNT);
            bl[idx].rc->Position
                = LT + Vector2(bl[idx].rc->Scale.x * j,
                    -bl[idx].rc->Scale.y * i);
            bl[idx].life = RndInt(1, 3);
            bl[idx].rc->color
                = Color(bl[idx].life / 4.0f, 0.5f, 0.5f,1.0f);

            bl[idx].rc->WorldUpdate();
        }
    }

    pl = new Rect();
    pl->Init();
    pl->Scale = Vector2(100.0f, 20.0f);
    pl->Position = Vector2(400.0f, 10.0f);

    ball = new Circle();
    ball->Init();
    ball->Scale = Vector2(20.0f, 20.0f);
    ball->Position = Vector2(400.0f, 300.0f);

    ballDir = DOWN;
    cor = 1.005f;
    return S_OK;
    //return E_FAIL;
}

void Scene1::Release()
{
    
}

void Scene1::Update()
{
    ImGui::SliderFloat("cor", &cor, 0.0f, 2.0f);

    if (KEYMANAGER->KeyPress(VK_LEFT))
    {
        pl->Position += LEFT * 150.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress(VK_RIGHT))
    {
        pl->Position += RIGHT * 150.0f * DeltaTime;
    }
    pl->WorldUpdate();

    ball->Position
        += ballDir * ballSpeed * DeltaTime;

    ball->WorldUpdate();

}

void Scene1::LateUpdate()
{
    //벽과 공 충돌
    if (ball->Position.x < 10.0f ||
        ball->Position.x >WINSIZEX - 10.0f)
    {
        ballDir.x *= -1.0f;//좌우반전
        ballSpeed *= cor;
       
    }
    if (ball->Position.y < 10.0f ||
        ball->Position.y >WINSIZEY - 10.0f)
    {
        ballDir.y *= -1.0f;//상하반전
        ballSpeed *= cor;
    }

    //플레이어와 공 충돌
    if (ColRectCir(pl, ball))
    {
        Vector2 dir
            = ball->Position - pl->Position;
        D3DXVec2Normalize(&dir, &dir);
        ballDir = dir;
        ballSpeed *= cor;
    }
    //공과 블럭과의 충돌
    for (int i = 0; i < BLOCKMAX; i++)
    {
        if (ColRectCir(bl[i].rc, ball))
        {
            /*Vector2 dir = ball->Position -
                bl[i].rc->Position;*/
            if ((bl[i].rc->Position.x -
                bl[i].rc->Scale.x * 0.5f < ball->Position.x) ||
                (bl[i].rc->Position.x +
                    bl[i].rc->Scale.x * 0.5f > ball->Position.x))
            {
                ballDir.y *= -1.0f;
            }
            else
            {
                ballDir.x *= -1.0f;
            }
            ballSpeed *= cor;
            //블럭 없애기
            bl[i].life--;
            bl[i].rc->color
                = Color(bl[i].life / 4.0f, 0.5f, 0.5f, 1.0f);
            if (bl[i].life < 1)
            {
                bl[i].rc->isActive = false;
            }

            break;
        }
    }


    pl->WorldUpdate();
    ball->WorldUpdate();
  
}

void Scene1::Render()
{
    for (int i = 0; i < BLOCKMAX; i++)
    {
        bl[i].rc->Render();
    }
    pl->Render();
    ball->Render();
}
