#include "stdafx.h"
#include "MainGame.h"
MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
    //타이머 생성(일정주기마다 WM_TIMER호출)
    srand((UINT)time(NULL));
    isVsync = false;
    //ImGui 생성
    ImGui::Create(g_hwnd, g_Device, g_DeviceContext);
    //다크테마
    ImGui::StyleColorsDark();

    Object::Axis = new Line();
    Object::Axis->Init();
    KEYMANAGER;

    sc1 = new Scene1();
    sc1->Init();
    sc2 = new Scene2();
    sc2->Init();

    pCurrentScene = sc1;

    return S_OK;
}

void MainGame::Release()
{
    sc1->Release();
    sc2->Release();
    delete sc1;
    delete sc2;
    KEYMANAGER->DeleteSingleton();
    TIMEMANAGER->DeleteSingleton();
    CAMMANAGER->DeleteSingleton();
    //생성된 타이머 해제
    ImGui::Delete();
    delete Object::Axis;
}

void MainGame::Update()
{
    ImGui::Update();
    ImGui::Text("FPS: %d", TIMEMANAGER->GetFrameRate());
    ImGui::Text("WorldTime: %f", TIMEMANAGER->GetWorldTime());
    ImGui::Text("Delata: %f", DeltaTime);
    ImGui::Checkbox("Vsync", &isVsync);
    KEYMANAGER->Update();

    if(GetAsyncKeyState(VK_F1)
        & 0x8000)
    {
        pCurrentScene = sc1;
    }
    if(GetAsyncKeyState(VK_F2)
        & 0x8000)
    {
        pCurrentScene = sc2;
    }
    if(pCurrentScene)
    {
        pCurrentScene->Update();
    }
    
}

void MainGame::LateUpdate()
{
    if(pCurrentScene)
    {
        pCurrentScene->LateUpdate();
    }
}

void MainGame::Render()
{
    //바탕색 깔기 g_RTV에 연결된 백버퍼가
    Color background = Color(0.5f, 0.5f, 0.5f, 1.0f);
    //그전에있던거 위에 바탕색깔기
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float *)background);

    CAMMANAGER->CameraUpdate();

    if(pCurrentScene)
    {
        pCurrentScene->Render();
    }
    ImGui::Render();
    //백 프론트 스왑  수직동기화?
    g_SwapChain->Present(isVsync, 0);
}
