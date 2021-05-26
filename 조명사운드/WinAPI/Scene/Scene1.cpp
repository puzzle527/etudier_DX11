#include "stdafx.h"
#include "Scene1.h"

//과제 원그리기
//회전이동크기 변환 구현

Scene1::Scene1()
{
    //생성후 바뀌지 않을것
    Bg = new Image(_T("back.png"));
    Bg->Init();
    Bg->Scale = Vector2(800.0f, 600.0f);
    Bg->Position = Vector2(400.0f, 300.0f);
    Bg->WorldUpdate();
    Bg->ChangeAddress(_WRAP);

    Floor = new Image(_T("floor.bmp"), Vector2(-0.5f, -0.5f));
    Floor->Init();
    Floor->Scale = Vector2(800.0f, 96.0f);
    Floor->WorldUpdate();
    Floor->ChangeAddress(_WRAP);

    Pl.Body = new Rect(Vector2(0.0f, -0.5f), false);
    Pl.Body->Init();

    Pl.Spin = new Image(_T("spin.bmp"), Vector2(0.0f, -0.5f));
    Pl.Spin->Init();
    Pl.Spin->Scale = Vector2(96.0f, 96.0f);
    Pl.Spin->MaxFrame.x = 5;//가로5분할 이미지
    Pl.Spin->P = &Pl.Body->RT;

    //48x60
    Pl.Run = new Image(_T("run.bmp"), Vector2(0.0f, -0.5f));
    Pl.Run->Init();
    Pl.Run->Scale = Vector2(96.0f, 120.0f);
    Pl.Run->MaxFrame.x = 4;//가로5분할 이미지
    Pl.Run->P = &Pl.Body->RT;

}

Scene1::~Scene1()
{
    delete Bg;
    delete Floor;
    delete Pl.Body;
    delete Pl.Spin;
    delete Pl.Run;
}

HRESULT Scene1::Init()
{ 
    
    //79x48 비율로 바닥 그리기

    
    //158사이즈일때 몇개나 들어오는지?
    Floor->UV.x = 0.0f;
    Floor->UV.z = 800.0f / 158.0f;
   
    Pl.Body->Position = Vector2(100.0f, 96.0f);

    //48x48
   
    //기본은 런상태
    Pl.State = RPL_RUN;
    Pl.Gravity = 0.0f;
    Pl.Body->Scale = Pl.Run->Scale;
    Pl.Body->Scale.x -= 20.0f;
    Pl.Spin->isActive = false;
    Pl.Run->isActive = true;
    Pl.Run->ChangeAnim(_LOOP, 0.1f);
   
    return S_OK;
}

void Scene1::Release()
{
}

void Scene1::Update()
{
    if (KEYMANAGER->KeyDown('1'))
    {
        SCENEMANAGER->ChangeScene("sc2")
            ->Init();
        Release();
    }



    //구름을 왼쪽으로 초당 30픽셀 이동시키기
    Bg->UV.x += DeltaTime / (800.0f / 30.0f);
    Bg->UV.z += DeltaTime / (800.0f / 30.0f);

    //바닥을 왼쪽으로 초당 100픽셀 이동시키기

    Floor->UV.x += DeltaTime / (158.0f / 100.0f);
    Floor->UV.z += DeltaTime / (158.0f / 100.0f);

    //런 상태에서만 키입력 허용
    if (Pl.State == RPL_RUN)
    {
        //슬라이드
        if (KEYMANAGER->KeyDown(VK_DOWN))
        {
            Pl.State = RPL_SLIDE;
            Pl.Body->Scale = Pl.Spin->Scale;
            Pl.Body->Scale.x -= 20.0f;
            Pl.Spin->isActive = true;
            Pl.Run->isActive = false;
            Pl.Spin->ChangeAnim(_ONCE, 0.1f);
        }

        //점프
        if (KEYMANAGER->KeyDown(VK_SPACE))
        {
            Pl.State = RPL_JUMP;
            Pl.Body->Scale = Pl.Spin->Scale;
            Pl.Body->Scale.x -= 20.0f;
            Pl.Spin->isActive = true;
            Pl.Run->isActive = false;
            Pl.Spin->ChangeAnim(_ONCE, 0.1f);
            //솟구치는 힘 크기
            Pl.Gravity = -500.0f;
        }
        
    }
    else if (Pl.State == RPL_SLIDE)
    {
        //런으로 바꿀 준비
        if (KEYMANAGER->KeyUp(VK_DOWN))
        {
            Pl.Spin->ChangeAnim(_MIRRORONCE, 0.1f);
            
        }
        if (Pl.Spin->GetAnimState() == _MIRRORONCE
            and Pl.Spin->Frame.x == 0)
        {
            Pl.State = RPL_RUN;
            Pl.Body->Scale = Pl.Run->Scale;
            Pl.Body->Scale.x -= 20.0f;
            Pl.Spin->isActive = false;
            Pl.Run->isActive = true;
            Pl.Run->ChangeAnim(_LOOP, 0.1f);
        }

    }
    //점프상태 일때
    else
    { 
        //중력의 영향 주기
        Pl.Body->Position
            += DOWN * Pl.Gravity * DeltaTime;
        Pl.Gravity += 400.0f * DeltaTime;
        
        //런으로 바꿀 준비
        if (Pl.Body->Position.y < 96.0f)
        {
            Pl.Body->Position.y = 96.0f;
            Pl.State = RPL_RUN;
            Pl.Body->Scale = Pl.Run->Scale;
            Pl.Body->Scale.x -= 20.0f;
            Pl.Spin->isActive = false;
            Pl.Run->isActive = true;
            Pl.Run->ChangeAnim(_LOOP, 0.1f);
        }

    }

    Pl.Spin->WorldUpdate();
    Pl.Run->WorldUpdate();
    Pl.Body->WorldUpdate();
}

void Scene1::LateUpdate()
{
    //위에서 바뀐 포지션같은걸로
    //충돌구현



    Pl.Spin->WorldUpdate();
    Pl.Run->WorldUpdate();
    Pl.Body->WorldUpdate();
}

void Scene1::Render()
{
    Bg->Render();
    Floor->Render();
   

    Pl.Spin->Render();
    Pl.Run->Render();
    Pl.Body->Render();
}
