#include "stdafx.h"
#include "Scene1.h"

HRESULT Scene1::Init()
{
    pl = new Rect();
    pl->Init();
    pl->Position = Vector2(400.0f, 300.0f);
    pl->Scale = Vector2(30.0f, 30.0f);


    Distance = 70.0f;
    Radius = 20.0f;
    Speed = 1.0f;

    child[0] = new Circle();
    child[0]->Init();
    child[0]->Position = Vector2(Distance, 0.0f);
    child[0]->Scale = Vector2(Radius, Radius);
    child[0]->P = &pl->RT;

    child[1] = new Circle();
    child[1]->Init();
    child[1]->Position = Vector2(-Distance, 0.0f);
    child[1]->Scale = Vector2(Radius, Radius);
    child[1]->P = &pl->RT;


    for (int i = 0; i < DDMAX; i++)
    {
        dd[i].cc = new Circle(36,Vector2(0.0f,0.5f));
        dd[i].cc->Init();
        dd[i].cc->Scale = Vector2(20.0f, 20.0f);
        
        dd[i].Reset(pl->Position);
    }

    for (int i = 0; i < BGMAX; i++)
    {
        bg[i] = new Star();
        bg[i]->Init();
        bg[i]->Scale = Vector2(100.0f, 100.0f);
        bg[i]->Position = Vector2(RndFloat(0.0f, 800.0f),
            RndFloat(000.0f, 600.0f));
        bg[i]->color =
            Color(RndFloat(), RndFloat(), RndFloat(), 0.5f);
        bg[i]->WorldUpdate();
    }

    return S_OK;
}

void Scene1::Release()
{
    delete pl;
    delete child[0];
    delete child[1];
    for (int i = 0; i < DDMAX; i++)
    {
        delete dd[i].cc;

    }
    for (int i = 0; i < BGMAX; i++)
    {
        delete bg[i];
    }
}

void Scene1::Update()
{
    //점수를 gui에 출력
    ImGui::Text("Score: %d", count);
    /*ImGui::Text("Score: %lf", count);
    ImGui::Text("Score: %f", count);
    ImGui::Text("Score: %s", count);*/

    if (ImGui::ColorEdit4("PlColor", pl->color))
    {
        cout << "컬러 바꾸는 중" << endl;
    }
    if (ImGui::SliderFloat2("PlPos", pl->Position, 0.0f, 1000.0f))
    {

        cout << "위치 바꾸는 중" << endl;
    }

    ImGui::SliderFloat("Distance",
        &Distance, 0.0f, 400.0f);
    ImGui::SliderFloat("Radius",
        &Radius, 0.0f, 400.0f);
    ImGui::SliderFloat("Speed",
        &Speed, 0.0f, 10.0f);
    ImGui::ColorEdit4("Child0Color", child[0]->color);
    ImGui::ColorEdit4("Child1Color", child[1]->color);

    //pl->color.r = RndFloat(0.5f,1.0f);
    if (KEYMANAGER->KeyPress('1'))
    {
        timeScale += DeltaTime;
        pl->color += Color(0.01f, 0.01f, 0.01f, 0.0f);
    }
    if (KEYMANAGER->KeyPress('2'))
    {
        timeScale -= DeltaTime;
        pl->color -= Color(0.01f, 0.01f, 0.01f, 0.0f);
    }
    //플레이어 움직임
    if(KEYMANAGER->KeyPress(VK_RIGHT))
    {
        CAMMANAGER->Pos += RIGHT * 200.0f * DeltaTime * timeScale;
        pl->Position += RIGHT * 200.0f * DeltaTime* timeScale;
    }
    if(KEYMANAGER->KeyPress(VK_LEFT))
    {
        CAMMANAGER->Pos += LEFT * 200.0f * DeltaTime * timeScale;
        pl->Position += LEFT * 200.0f * DeltaTime* timeScale;
    }
    if (KEYMANAGER->KeyPress(VK_UP))
    {
        CAMMANAGER->Pos += UP * 200.0f * DeltaTime * timeScale;
        pl->Position += UP * 200.0f * DeltaTime * timeScale;
    }
    if (KEYMANAGER->KeyPress(VK_DOWN))
    {
        CAMMANAGER->Pos += DOWN * 200.0f * DeltaTime * timeScale;
        pl->Position += DOWN * 200.0f * DeltaTime * timeScale;
    }
    //DD 움직임
    for (int i = 0; i < DDMAX; i++)
    {
        dd[i].lifeTime -= DeltaTime * dd[i].speed *0.01f * timeScale;
        dd[i].cc->Position
            += dd[i].dir * dd[i].speed * DeltaTime* timeScale;
    }
    //월드 갱신

    child[0]->Scale = Vector2(Radius, Radius);
    child[1]->Scale = Vector2(Radius, Radius);
    child[0]->Position = Vector2(Distance, 0.0f);
    child[1]->Position = Vector2(-Distance, 0.0f);
    child[0]->Rotation2 += DeltaTime * Speed;
    child[1]->Rotation2 += DeltaTime * Speed;

    pl->WorldUpdate();
    child[0]->WorldUpdate();
    child[1]->WorldUpdate();
    for (int i = 0; i < DDMAX; i++)
    {
        //ImGui::ColorEdit4("bl", dd[i].cc->color);
        dd[i].cc->WorldUpdate();
    }



}

void Scene1::LateUpdate()
{
    for (int i = 0; i < DDMAX; i++)
    {
        //DD와 위성과 충돌
        if (ColCir(child[0], dd[i].cc))
        {
            dd[i].Reset(pl->Position);
        }
        if (ColCir(child[1], dd[i].cc))
        {
            dd[i].Reset(pl->Position);
        }
        //플레이어와 DD충돌
        if (ColRectCir(pl,dd[i].cc))
        {
            //timeScale = 0.0f;
        }

        //라이프타임이 0보다 작을때
        if (dd[i].lifeTime < 0.0f)
        {
            count++;
            //cout << "점수:" << count << endl;
            dd[i].Reset(pl->Position);
            //timeScale += 0.01f;
            //timeScale = Saturate(timeScale, 0.0f, 3.0f);
        }
    }

}

void Scene1::Render()
{
    for (int i = 0; i < BGMAX; i++)
    {
        bg[i]->Render();
    }

    pl->Render();
    child[0]->Render();
    child[1]->Render();
    for (int i = 0; i < DDMAX; i++)
    {
        dd[i].cc->Render();
    }
}

void DD::Reset(Vector2 Pos)
{
    float Radian = RndFloat(0.0f, 2.0f * PI);
    float Radius = RndFloat(500.0f, 800.0f);
    cc->Position =
        Vector2(Pos.x + cosf(Radian) * Radius,
            Pos.y + sinf(Radian) * Radius);
    speed = RndFloat(200.0f, 400.0f);
    cc->color =
        Color(RndFloat(), RndFloat(), RndFloat(), 0.5f);
    //x , y
    dir = (Pos + Vector2(RndFloat(-200.0f, 200.0f),
        RndFloat(-200.0f, 200.0f)) )- cc->Position;
    D3DXVec2Normalize(&dir, &dir);
    lifeTime = 15.0f;
}

