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
    srand((UINT)time(NULL));
    isVsync = false;
    Object::Axis = new Line();
    Object::Axis->Init();
    KEYMANAGER; //키매니저 할당
    //ImGui 생성
    ImGui::Create(g_hwnd, g_Device, g_DeviceContext);
    //다크테마
    ImGui::StyleColorsDark();


    sc1 = new Scene1();
    sc1->Init();
    sc2 = new Scene2();
    sc2->Init();
    CurrentScene = sc2;


    POINT a;

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

    ImGui::Delete();
   
    delete Object::Axis;
}

void MainGame::Update()
{
    ImGui::Update();
    ImGui::Text("FPS: %d", TIMEMANAGER->GetFrameRate());
    ImGui::Text("WorldTime: %f", TIMEMANAGER->GetWorldTime());
    ImGui::Text("Delata: %f", DeltaTime);
    // bool값 스위칭
    ImGui::Checkbox("Vsync", &isVsync);

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
    Color background = Color(1.0f, 1.0f, 1.0f, 1.0f);
    //그전에있던거 위에 바탕색깔기
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float *)background);

    CAMMANAGER->CameraUpdate();

    if(CurrentScene)
    {
        CurrentScene->Render();
    }
    ImGui::Render();
    //백 프론트 스왑      수직동기화?
    g_SwapChain->Present(isVsync, 0);
}
