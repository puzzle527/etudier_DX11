#include "stdafx.h"
#include "MainGame.h"

//����

//�� �̵�, Ȯ�� ��� ,ȸ�� ����


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
    // bool�� ����Ī
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
    //������ ��� g_RTV�� ����� ����۰�
    Color background = Color(1.0f, 1.0f, 1.0f, 1.0f);
    //�������ִ��� ���� ���������
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float *)background);

    CAMMANAGER->CameraUpdate();

    if(CurrentScene)
    {
        CurrentScene->Render();
    }
    ImGui::Render();
    //�� ����Ʈ ����      ��������ȭ?
    g_SwapChain->Present(isVsync, 0);
}
