#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{

    cc1 = new Rect(Vector2(-0.3f,0.0f));
    cc1->Init();
    cc1->Scale = Vector2(250.0f, 100.0f);
    cc1->Position = Vector2(400.0f, 300.0f);
    //cc1->Rotation = 1.0f;
    cc1->isAxis = true;

    cc = new Rect();
    cc->Init();
    cc->Scale = Vector2(200.0f,200.0f);
    cc->Position = Vector2(150.0f,150.0f);
    //cc->Rotation = 1.0f;
    cc->isAxis = true;

    //cc->P = &cc1->RT;

    return S_OK;
}

void Scene2::Release()
{
    delete cc;
    delete cc1;
}

void Scene2::Update()
{
    //이전 프레임과 현재 프레임의 차이값
    Vector2 Dis = g_Mouse - LastMouse;

    if (KEYMANAGER->KeyPress(VK_LEFT))
    {
        cc->Scale.x += 100.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress(VK_RIGHT))
    {
        cc->Scale.x -= 100.0f * DeltaTime;
    }

    //cc와 마우스가 겹쳐 있을때
    if (ColRectPt(cc, g_Mouse))
    {
        //겹쳐있으면서 마우스 좌클릭을 했다면
        if (KEYMANAGER->KeyPress(VK_LBUTTON))
        {
            cc->Position += Dis;
        }
    }
    if (AABB(cc1, cc))
    {
        cout << TIMEMANAGER->GetWorldTime()
            << endl;
    }


    //갱신
    LastMouse = g_Mouse;

}

void Scene2::LateUpdate()
{
    cc->WorldUpdate();
    cc1->WorldUpdate();
}

void Scene2::Render()
{
    cc->Render();
    cc1->Render();
}
