#include "stdafx.h"
#include "Scene2.h"

//행성의 움직임을 프레임에 영향을 안받도록
//스페이스바 누르면 태양이 딱 2초간만 회전

HRESULT Scene2::Init()
{
    rc1 = new Rect(Vector2(0.5f, 0.0f));
    rc1->Init();
    rc1->Position = Vector2(400.0f, 400.0f);
    rc1->Scale = Vector2(100.0f, 200.0f);

    rc2 = new Rect(Vector2(-0.5f, 0.0f));
    rc2->Init();
    rc2->Position = Vector2(100.0f, 100.0f);
    rc2->Scale = Vector2(200.0f, 100.0f);


    return S_OK;
}

void Scene2::Release()
{
    delete rc1;
    delete rc2;
}

void Scene2::Update()
{
    if(KEYMANAGER->KeyPress('W'))
    {
        rc1->Position += UP * 100.0f * DeltaTime;
    }
    if(KEYMANAGER->KeyPress('S'))
    {
        rc1->Position += DOWN * 100.0f * DeltaTime;
    }

    if(KEYMANAGER->KeyPress('A'))
    {
        rc1->Position += LEFT * 100.0f * DeltaTime;
    }
    //오른쪽회전
    if(KEYMANAGER->KeyPress('D'))
    {
        rc1->Position += RIGHT * 100.0f * DeltaTime;
    }

    //충돌전 월드값 갱신
    rc1->WorldUpdate();
    rc2->WorldUpdate();
}

void Scene2::LateUpdate()
{
   //충돌 체크

    if (AABB(rc1, rc2))
    {
        cout << TIMEMANAGER->GetWorldTime() << endl;
    }

}

void Scene2::Render()
{
    rc1->Render();
    rc2->Render();
}
