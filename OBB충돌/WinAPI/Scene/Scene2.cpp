#include "stdafx.h"
#include "Scene2.h"
Scene2::Scene2()
{

}
Scene2::~Scene2()
{
}
HRESULT Scene2::Init()
{
    Pl = new Image(_T("Walk.png"));
    Pl->Init();
    Pl->Position = Vector2(400.0f, 300.0f);
    Pl->Scale = Vector2(100.0f, 100.0f);
    Pl->MaxFrame.x = 6;
    Pl->MaxFrame.y = 8;
    Pl->ChangeAnim(_LOOP, 0.1f);

    return S_OK;
}

void Scene2::Release()
{
}

void Scene2::Update()
{
    ImGui::SliderInt("YFRAME", &Pl->Frame.y, 0, 7);


    Pl->WorldUpdate();
}

void Scene2::LateUpdate()
{
}

void Scene2::Render()
{

    Pl->Render();
}
