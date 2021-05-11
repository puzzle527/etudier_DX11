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
    bono1->color = Color(1, 1, 1, 1);
    bono2 = new Image(_T("bono/bono.jpg"));
    bono2->Init();
    bono2->Position = Vector2(600.0f, 300.0f);
    bono2->Scale = Vector2(200.0f, 200.0f);
    bono2->UV.x = 66.0f / 225.0f;
    bono2->UV.y = 91.0f / 225.0f;
    bono2->UV.z = 181.0f / 225.0f;
    bono2->UV.w = 183.0f / 225.0f;

    return S_OK;
}

void Scene1::Release()
{
    
}

void Scene1::Update()
{
    ImGui::ColorEdit4("bono1Color", bono1->color);


    bono1->WorldUpdate();
    bono2->WorldUpdate();
}

void Scene1::LateUpdate()
{
   
}

void Scene1::Render()
{
    bono1->Render();
    bono2->Render();
}
