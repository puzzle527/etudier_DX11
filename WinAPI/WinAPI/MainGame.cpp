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
    //Ÿ�̸� ����(�����ֱ⸶�� WM_TIMERȣ��)
    Object::Axis = new Line();
    Object::Axis->Init();
    KEYMANAGER; //Ű�Ŵ��� �Ҵ�
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

    //������ Ÿ�̸� ����
   
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
    //������ ��� g_RTV�� ����� ����۰�
    Color background = Color(0.5f, 0.5f, 0.5f, 1.0f);
    //�������ִ��� ���� ���������
    g_DeviceContext->ClearRenderTargetView(g_RTV, (float *)background);

    CAMMANAGER->CameraUpdate();

    if(CurrentScene)
    {
        CurrentScene->Render();
    }

    //�� ����Ʈ ����
    g_SwapChain->Present(0, 0);
}
