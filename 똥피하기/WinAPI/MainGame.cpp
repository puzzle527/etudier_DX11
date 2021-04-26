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
    //Ÿ�̸� ����(�����ֱ⸶�� WM_TIMERȣ��)
    srand((UINT)time(NULL));
    isVsync = false;
    //ImGui ����
    ImGui::Create(g_hwnd, g_Device, g_DeviceContext);
    //��ũ�׸�
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
    //������ Ÿ�̸� ����
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
    //������ ��� g_RTV�� ����� ����۰�
    Color background = Color(0.5f, 0.5f, 0.5f, 1.0f);
    //�������ִ��� ���� ���������
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float *)background);

    CAMMANAGER->CameraUpdate();

    if(pCurrentScene)
    {
        pCurrentScene->Render();
    }
    ImGui::Render();
    //�� ����Ʈ ����  ��������ȭ?
    g_SwapChain->Present(isVsync, 0);
}
