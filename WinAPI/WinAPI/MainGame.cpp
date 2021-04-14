#include "stdafx.h"
#include "MainGame.h"

//과제

//별 이동, 확대 축소 ,회전 구현


MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
    //타이머 생성(일정주기마다 WM_TIMER호출)
    Object::Axis = new Line();
    Object::Axis->Init();
    KEYMANAGER; //키매니저 할당
	srand(time(NULL));


    sc1 = new Scene1();
    sc1->Init();
    sc2 = new Scene2();
    sc2->Init();
    CurrentScene = sc2;
    return S_OK;
}

void MainGame::Release()
{
    KEYMANAGER->DeleteSingleton();
    TIMEMANAGER->DeleteSingleton();
    CAMMANAGER->DeleteSingleton();

    sc1->Release();
    delete sc1;

    sc2->Release();
    delete sc2;

    //생성된 타이머 해제
   
    delete Object::Axis;
}

void MainGame::Update()
{
    KEYMANAGER->Update();
    if(KEYMANAGER->KeyDown(VK_F1))
    {
        CurrentScene = sc1;
    }
    if(KEYMANAGER->KeyDown(VK_F2))
    {
        CurrentScene = sc2;
    }
    if(CurrentScene)
    {
        CurrentScene->Update();
    }
   
}

void MainGame::LateUpdate()
{
    if(CurrentScene)
    {
        CurrentScene->LateUpdate();
    }
    
}

void MainGame::Render()
{
    //바탕색 깔기 g_RTV에 연결된 백버퍼가
    Color background = Color(0.5f, 0.5f, 0.5f, 1.0f);
    //그전에있던거 위에 바탕색깔기
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float *)background);

    CAMMANAGER->CameraUpdate();

    if(CurrentScene)
    {
        CurrentScene->Render();
    }

    //백 프론트 스왑
    g_SwapChain->Present(0, 0);
}
