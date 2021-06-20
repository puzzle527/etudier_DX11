#include "stdafx.h"
#include "Scene2.h"
#include "Player\Player.h"

Scene2::Scene2()
{
    Pl = new Player();

}
Scene2::~Scene2()
{
    delete Pl;
}
HRESULT Scene2::Init()
{
    Pl->Init();

    return S_OK;
}

void Scene2::Release()
{
}

void Scene2::Update()
{
    Pl->Update();
}

void Scene2::LateUpdate()
{
    Pl->LateUpdate();
}

void Scene2::Render()
{

    Pl->Render();
}
