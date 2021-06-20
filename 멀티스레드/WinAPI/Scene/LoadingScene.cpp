#include "stdafx.h"
#include "LoadingScene.h"
#include "Scene/Scene1.h"
#include "Scene/Scene2.h"
#include "Scene/Scene3.h"
int LoadCount = 0; //해당cpp에서 사용가능한 데이터영역
mutex m;

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

HRESULT LoadingScene::Init()
{
    //CreateScene 을 실행하는 스레드 생성
    p1 = thread(CreateScene);

    Bar = new Rect(Vector2(-0.5f, 0.0f));
    Bar->Init();
    Bar->Position = Vector2(0, 200);
    Bar->Scale = Vector2(100, 100);
    Bar->color = Color(1, 0, 0, 1);

    return S_OK;
}

void LoadingScene::Release()
{
  
}

void LoadingScene::Update()
{
    if (LoadCount == 3)
    {
        SCENEMANAGER->ChangeScene("sc2")
            ->Init();
        p1.join();
    }
    Bar->WorldUpdate();
}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::Render()
{
    Bar->Scale.x = WINSIZEX * LoadCount / 3;
    Bar->color = Color(RndFloat(), 0, 0, 1);
    Bar->Render();
}

void LoadingScene::TextRender()
{
   
}

void LoadingScene::CreateScene()
{
    
    Scene* temp;
    temp = new Scene1();
    m.lock();
        SCENEMANAGER->AddScene("sc1", temp);
        cout << "sc1 Create" << endl;
        LoadCount++;
        /*while (1)
        {
            cout << "while" << endl;
        }*/
    m.unlock();
       
    temp = new Scene2();
    m.lock();
        SCENEMANAGER->AddScene("sc2", temp);
        cout << "sc2 Create" << endl;
        LoadCount++;
    m.unlock();
        Sleep(5000);
    temp = new Scene3();
    m.lock();
        SCENEMANAGER->AddScene("sc3", temp);
        cout << "sc3 Create" << endl;
        LoadCount++;
    m.unlock();
}
