#include "stdafx.h"
#include "Scene1.h"

//���� ���׸���
//ȸ���̵�ũ�� ��ȯ ����

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

    //����׿�

    //��ư���� ���콺�� Ŭ���Ҷ� true��ȯ

    //�÷�����         ���ڿ�       ������ ��
    ImGui::ColorEdit4("PlColor", player->color);
    //�����̴�           ���ڿ�     �����Ұ�        �ּ�     �ִ�
    ImGui::SliderFloat("PlRot", &player->Rotation,0.0f,2.0f*PI);
    ImGui::SliderFloat2("PlScale", player->Scale,0.0f, 400.0f);
    if (ImGui::SliderFloat2("PlPos",
        player->Position, -400.0f, 400.0f))
    {
        //�����ϰ� ������
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

    //����׿� ġƮ
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

    //�÷��̾����� ���������� �����ϰ� �����
    //player->color = Color(RndFloat(0.5f,1.0f), 0.5f, 0.5f, 1.0f);


    //pos,scale,rot �� �ٲٱ�
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


    //W��� ����
    player->WorldUpdate();
    for (int i = 0; i < DROPMAX; i++)
    {
        dr[i].cc->WorldUpdate();
    }
}

void Scene1::LateUpdate()
{
    //�浹

    
    for (int i = 0; i < DROPMAX; i++)
    {
        // Drop�� �÷��̾�� 700��ŭ �־�������
        Vector2 Dis = dr[i].cc->Position - player->Position;
        if ( Length(&Dis) > 700.0f)
        {
            dr[i].Reset(player->Position);
            timeScale += 0.0005f;
            Score++;
            cout << "����:" << Score << endl;
        }
        //�÷��̾�� drop �浹
        if(ColRectCir(player, dr[i].cc))
        {
            //����
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
