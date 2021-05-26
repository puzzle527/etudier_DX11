#include "stdafx.h"
#include "Scene1.h"

//과제 원그리기
//회전이동크기 변환 구현

HRESULT Scene1::Init()
{ 
    bono1 = new Image(_T("bono1.png"));
    bono1->Init();
    bono1->Position = Vector2(200.0f, 300.0f);
    bono1->Scale = Vector2(200.0f, 200.0f);
    
    bono1rc = new Rect(Vector2(0.0f,0.0f),false);
    bono1rc->Init();
    bono1rc->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    bono1rc->Scale = Vector2(150.0f, 150.0f);
    bono1rc->P = &bono1->RT;

    bono2 = new Image(_T("bono/bono.jpg"));
    bono2->Init();
    bono2->Position = Vector2(600.0f, 300.0f);
    bono2->Scale = Vector2(200.0f, 200.0f);
    bono2->UV.x = 66.0f / 225.0f;
    bono2->UV.y = 91.0f / 225.0f;
    bono2->UV.z = 181.0f / 225.0f;
    bono2->UV.w = 183.0f / 225.0f;

    bono2cc = new Circle(100,Vector2(0.0f,0.0f),false);
    bono2cc->Init();
    bono2cc->Scale = Vector2(200.0f, 200.0f);
    bono2cc->P = &bono2->RT;
    bono2cc->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    return S_OK;
}

void Scene1::Release()
{
    
}

void Scene1::Update()
{
    ImGui::ColorEdit4("bono1Color", bono1->color);

    if (ColRectPt(bono1rc, g_Mouse))
    {
        bono1->color.r = RndFloat(0.5f, 1.0f);
    }
    else
    {
        bono1->color.r = 0.5f;
    }
    if (ColCirPt(bono2cc, g_Mouse))
    {
        bono2->color.a = RndFloat(0.0f, 1.0f);
    }
    else
    {
        bono2->color.a = 0.5f;
    }


    bono1->WorldUpdate();
    bono2->WorldUpdate();
    bono1rc->WorldUpdate();
    bono2cc->WorldUpdate();
}

void Scene1::LateUpdate()
{
   
}

void Scene1::Render()
{
    bono1->Render();
    bono2->Render();
    bono1rc->Render();
    bono2cc->Render();
}
