#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
    st = new Star();
    st->Init();
    st->Scale = Vector2(300.0f,300.0f);
    st->Position = Vector2(400.0f,300.0f);
    st->isAxis = true;

    return S_OK;
}

void Scene2::Release()
{
    delete st;
}

void Scene2::Update()
{
    //Sun->Rotation +=0.05f;

    if(KEYMANAGER->KeyPress('A'))
    {
    }
    if(KEYMANAGER->KeyPress('D'))
    {
    }

}

void Scene2::LateUpdate()
{
    st->WorldUpdate();
}

void Scene2::Render()
{
    st->Render();
}
