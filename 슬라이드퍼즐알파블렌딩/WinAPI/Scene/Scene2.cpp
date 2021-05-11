#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Puzzle[i][j] = new Image(_T("bono1.png"),
                Vector2(-0.5f,-0.5f));
            Puzzle[i][j]->Init();
            Puzzle[i][j]->Scale = Vector2(200.0f, 200.0f);
            Puzzle[i][j]->Position = Vector2(200.0f * j, 200.0f * i);
            Puzzle[i][j]->UV.x =  j / 3.0f;
            Puzzle[i][j]->UV.z = (j + 1)/ 3.0f;
            Puzzle[i][j]->UV.y = (2 - i) / 3.0f;
            Puzzle[i][j]->UV.w = (3 - i) / 3.0f;
        }
    }
    //비어있는 좌표
    Null = Int2(0, 0);

  
    return S_OK;
}

void Scene2::Release()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            delete Puzzle[i][j];
        }
    }

}

void Scene2::Update()
{
    ImGui::ColorEdit4("NULLColor",
        Puzzle[Null.x][Null.y]->color);


    if (KEYMANAGER->KeyDown(VK_LEFT))
    {
        //좌표일때 장점
        if (Null.y > 0)
        {
            MySwap(Puzzle[Null.x][Null.y]->UV,
                Puzzle[Null.x][Null.y-1]->UV);
            Null.y--;
        }
    }
    if (KEYMANAGER->KeyDown(VK_RIGHT))
    {
        if (Null.y < 2)
        {
            MySwap(Puzzle[Null.x][Null.y]->UV,
                Puzzle[Null.x][Null.y + 1]->UV);
            Null.y++;
        }
    }
    if (KEYMANAGER->KeyDown(VK_UP))
    {
        if (Null.x < 2)
        {
            MySwap(Puzzle[Null.x][Null.y]->UV,
                Puzzle[Null.x + 1][Null.y ]->UV);
            Null.x++;
        }
    }
    if (KEYMANAGER->KeyDown(VK_DOWN))
    {
        if (Null.x > 0)
        {
            MySwap(Puzzle[Null.x][Null.y]->UV,
                Puzzle[Null.x - 1][Null.y]->UV);
            Null.x--;
        }
    }


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Puzzle[i][j]->WorldUpdate();
        }

    }
}

void Scene2::LateUpdate()
{

}

void Scene2::Render()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //if (Null == Int2(i, j))continue;

            Puzzle[i][j]->Render();
        }

    }
}

