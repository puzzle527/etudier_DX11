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
    KEYMANAGER; //Ű�Ŵ��� �Ҵ�
    //ImGui ����
    ImGui::Create(g_hwnd, g_Device, g_DeviceContext);
    //��ũ�׸�
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
    // bool�� ����Ī
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
    //������ ��� g_RTV�� ����� ����۰�
    Color background = Color(0.5f, 0.5f, 0.5f, 1.0f);
    //�������ִ��� ���� ���������
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float *)background);

    LIGHTMANAGER->LightUpdate();

    CAMMANAGER->CameraUpdate();

    if(SCENEMANAGER->GetCurrentScene())
    {
        SCENEMANAGER->GetCurrentScene()->Render();
    }
    ImGui::Render();
    //�� ����Ʈ ����      ��������ȭ?
    g_SwapChain->Present(isVsync, 0);
}
