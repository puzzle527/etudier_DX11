#include "stdafx.h"
#include "MainGame.h"
#include "Scene/LoadingScene.h"



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
    temp = new LoadingScene();
    SCENEMANAGER->AddScene("loading", temp);

    SCENEMANAGER->ChangeScene("loading")
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
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float*)background);


    LIGHTMANAGER->LightUpdate();

    CAMMANAGER->CameraUpdate();

    if(SCENEMANAGER->GetCurrentScene())
    {
        SCENEMANAGER->GetCurrentScene()->Render();
    }
   
    
}

void MainGame::TextRender()
{
    //스왑체인에서 hdc받아오기
    IDXGISurface1* Surface;
    g_SwapChain->GetBuffer(0, IID_PPV_ARGS(&Surface));
    Surface->GetDC(0, &g_hdc);
    //텍스트 배경색 없애기
    SetBkMode(g_hdc, 1);


    if (SCENEMANAGER->GetCurrentScene())
    {
        SCENEMANAGER->GetCurrentScene()->TextRender();
    }



    Surface->ReleaseDC(0);
    //렌더타겟 재설정
    g_DeviceContext->OMSetRenderTargets(1, &g_RTV, NULL);


    ImGui::Render();
    //백 프론트 스왑      수직동기화?
    g_SwapChain->Present(isVsync, 0);
}
