#include "stdafx.h"
#include "Scene1.h"

//과제 원그리기
//회전이동크기 변환 구현

HRESULT Scene1::Init()
{
    player = new Rect();
    player->Init();
    player->Position = Vector2(400.0f, 300.0f);
    player->Scale = Vector2(20.0f, 20.0f);

    for (int i = 0; i < DROPMAX; i++)
    {
        dr[i].cc = new Circle(50,Vector2(0.0f,-0.5f));
        dr[i].cc->Init();
        dr[i].cc->Scale = Vector2(15.0f, 15.0f);
        dr[i].Reset(player->Position);
    }
    for (int i = 0; i < BGMAX; i++)
    {
        bg[i] = new Star();
        bg[i]->Init();
        bg[i]->Scale = Vector2(100.0f, 100.0f);
        bg[i]->Position = Vector2(RndFloat(0.0f, 800.0f),
            RndFloat(000.0f, 600.0f));
        bg[i]->color =
            Color(RndFloat(), RndFloat(), RndFloat(), 0.5f);
        bg[i]->WorldUpdate();
    }

    return S_OK;
    //return E_FAIL;
}

void Scene1::Release()
{
    delete player;
    for (int i = 0; i < DROPMAX; i++)
    {
        delete dr[i].cc;

    }
    for (int i = 0; i < BGMAX; i++)
    {
        delete bg[i];
    }
}

void Scene1::Update()
{

    //디버그용

    //버튼들을 마우스로 클릭할때 true반환

    //컬러에딧         문자열       변경할 색
    ImGui::ColorEdit4("PlColor", player->color);
    //슬라이더           문자열     변경할값        최소     최대
    ImGui::SliderFloat("PlRot", &player->Rotation,0.0f,2.0f*PI);
    ImGui::SliderFloat2("PlScale", player->Scale,0.0f, 400.0f);
    if (ImGui::SliderFloat2("PlPos",
        player->Position, -400.0f, 400.0f))
    {
        //수정하고 있을때
        CAMMANAGER->Pos
            = player->Position - Vector2(400.0f, 300.0f);
    }
    if (ImGui::Button("Start"))
    {
        timeScale = 1.0f;
    }
    if (ImGui::Button("Stop"))
    {
        timeScale = 0.0f;
    }

    //디버그용 치트
    if (KEYMANAGER->KeyPress('1'))
    {
        timeScale += DeltaTime;
        player->color += Color(DeltaTime, DeltaTime, DeltaTime, 1.0f);
    }
    if (KEYMANAGER->KeyPress('2'))
    {
        timeScale -= DeltaTime;
        player->color -= Color(DeltaTime, DeltaTime, DeltaTime, 1.0f);
    }

    //플레이어한테 빨간색으로 점멸하게 만들기
    //player->color = Color(RndFloat(0.5f,1.0f), 0.5f, 0.5f, 1.0f);


    //pos,scale,rot 값 바꾸기
    if (KEYMANAGER->KeyPress(VK_LEFT))
    {
        player->Position += LEFT * 200.0f *DeltaTime * timeScale;
        CAMMANAGER->Pos += LEFT * 200.0f *DeltaTime * timeScale;
    }
    if (KEYMANAGER->KeyPress(VK_RIGHT))
    {
        player->Position += RIGHT * 200.0f * DeltaTime * timeScale;
        CAMMANAGER->Pos += RIGHT * 200.0f * DeltaTime * timeScale;
    }
    if (KEYMANAGER->KeyPress(VK_UP))
    {
        player->Position += UP * 200.0f * DeltaTime * timeScale;
        CAMMANAGER->Pos += UP * 200.0f * DeltaTime * timeScale;
    }
    if (KEYMANAGER->KeyPress(VK_DOWN))
    {
        player->Position += DOWN * 200.0f * DeltaTime * timeScale;
        CAMMANAGER->Pos += DOWN * 200.0f * DeltaTime * timeScale;
    }
    for (int i = 0; i < DROPMAX; i++)
    {
        //ImGui::ColorEdit4("dr", dr[i].cc->color);
        dr[i].cc->Position
            += dr[i].Dir * dr[i].Speed * DeltaTime * timeScale;

    }


    //W행렬 갱신
    player->WorldUpdate();
    for (int i = 0; i < DROPMAX; i++)
    {
        dr[i].cc->WorldUpdate();
    }
}

void Scene1::LateUpdate()
{
    //충돌

    
    for (int i = 0; i < DROPMAX; i++)
    {
        // Drop이 플레이어랑 700만큼 멀어졌을떄
        Vector2 Dis = dr[i].cc->Position - player->Position;
        if ( Length(&Dis) > 700.0f)
        {
            dr[i].Reset(player->Position);
            timeScale += 0.0005f;
            Score++;
            cout << "점수:" << Score << endl;
        }
        //플레이어와 drop 충돌
        if(ColRectCir(player, dr[i].cc))
        {
            //멈춰
            timeScale = 0.0f;
        }

    }


}

void Scene1::Render()
{
    for (int i = 0; i < BGMAX; i++)
    {
        bg[i]->Render();
    }
    
    player->Render();
    for (int i = 0; i < DROPMAX; i++)
    {
        dr[i].cc->Render();
    }
}
