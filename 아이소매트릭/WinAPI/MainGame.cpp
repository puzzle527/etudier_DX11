#include "stdafx.h"
#include "MainGame.h"

#include "Scene/Scene1.h"
#include "Scene/Scene2.h"
#include "Scene/Scene3.h"



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


    Scene* temp;
    temp = new Scene1();
    SCENEMANAGER->AddScene("sc1", temp);


    temp = new Scene2();
    SCENEMANAGER->AddScene("sc2", temp);

    temp = new Scene3();
    SCENEMANAGER->AddScene("sc3", temp);

    SCENEMANAGER->ChangeScene("sc2")
        ->Init();

    return S_OK;
}

void MainGame::Release()
{
    KEYMANAGER->DeleteSingleton();
    TIMEMANAGER->DeleteSingleton();
    CAMMANAGER->DeleteSingleton();
    LIGHTMANAGER->DeleteSingleton();
    SCENEMANAGER->DeleteSingleton();
    SOUNDMANAGER->DeleteSingleton();
    RESOURCEMANAGER->DeleteSingleton();

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
    if(SCENEMANAGER->GetCurrentScene())
    {
        SCENEMANAGER->GetCurrentScene()->Update();
    }
   
}

void MainGame::LateUpdate()
{
    if(SCENEMANAGER->GetCurrentScene())
    {
        SCENEMANAGER->GetCurrentScene()->LateUpdate();
    }
    
}

void MainGame::Render()
{
    //바탕색 깔기 g_RTV에 연결된 백버퍼가
    Color background = Color(0.5f, 0.5f, 0.5f, 1.0f);
    //그전에있던거 위에 바탕색깔기
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float *)background);

    LIGHTMANAGER->LightUpdate();

    CAMMANAGER->CameraUpdate();

    if(SCENEMANAGER->GetCurrentScene())
    {
        SCENEMANAGER->GetCurrentScene()->Render();
    }
    ImGui::Render();
    //백 프론트 스왑      수직동기화?
    g_SwapChain->Present(isVsync, 0);
}
