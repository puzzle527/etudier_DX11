#include "stdafx.h"
#include "Scene1.h"

//런게임 만들기 (쿠키런,윈드러너)

Scene1::Scene1()
{
    rc[0] = new Rect(Vector2(0.5f, 0.0f));
    rc[0]->Init();
    rc[0]->Position = Vector2(200.0f, 200.0f);
    rc[0]->Scale = Vector2(100.0f, 200.0f);

    rc[1] = new Rect(Vector2(0.0f, 0.5f));
    rc[1]->Init();
    rc[1]->Position = Vector2(500.0f, 200.0f);
    rc[1]->Scale = Vector2(200.0f, 100.0f);


}

Scene1::~Scene1()
{
    delete rc[1];
    delete rc[0];
}

HRESULT Scene1::Init()
{

    return S_OK;
}

void Scene1::Release()
{

}

void Scene1::Update()
{
    rc[0]->Position = g_Mouse;

    ImGui::SliderAngle("rc1",
        &rc[0]->Rotation.z);
    ImGui::SliderAngle("rc2",
        &rc[1]->Rotation.z);

    rc[0]->WorldUpdate();
    rc[1]->WorldUpdate();
}

void Scene1::LateUpdate()
{

    if (OBB(rc[1], rc[0]))
    {
        rc[0]->color.r = RndFloat();
    }

}

void Scene1::Render()
{

    rc[0]->Render();
    rc[1]->Render();
}
