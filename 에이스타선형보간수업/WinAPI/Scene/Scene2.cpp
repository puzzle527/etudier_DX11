#include "stdafx.h"
#include "Scene2.h"
#include "Player\Player.h"
#include "Player\Monster.h"
#include "TileMap\TileMap.h"

Scene2::Scene2()
{
    Tm = new TileMap();
    TileImg temp;
    //0�� Ÿ�� �߰�
    temp.file = _T("Tile.png");
    temp.MaxFrame = Int2(8, 6);
    Tm->Images.push_back(temp);
    //1�� Ÿ���߰�
    temp.file = _T("Tile2.png");
    temp.MaxFrame = Int2(11, 7);
    Tm->Images.push_back(temp);

    Pl = new Player();
    Mon = new Monster();
    Mon->Setpl(Pl);



}
Scene2::~Scene2()
{
    delete Pl;
    delete Mon;
    delete Tm;
}
HRESULT Scene2::Init()
{

    Pl->Init();
    Mon->Init();

    Tm->Init();
    Tm->Load("Save/map1.txt");
    return S_OK;
}

void Scene2::Release()
{
}

void Scene2::Update()
{
    Pl->Update();
    Mon->Update();
    Tm->Update();
}

void Scene2::LateUpdate()
{
    //ĳ���Ͱ� �����̰� ���Ŀ�
    // ����ġ�� Ÿ�ϸ� ���º�
    Int2 idx;
    if (Tm->VectorToIdx(Pl->GetFoot(), idx))
    {
        if (Tm->Tiles[idx.x][idx.y].state
            == TILE_WALL)
        {
            Pl->Move(false);
            Pl->Move2();
        }
    }

    if (KEYMANAGER->KeyDown('3'))
    {
        vector<Tile*> way;
        if (Tm->PathFinding(Int2(0, 0), Int2(3, 5), way))
        {
            for (int i = 0; i < way.size(); i++)
            {
               cout<< way[i]->TileIdx.x << ","
                   << way[i]->TileIdx.y << endl;
            }
        }
    }
    //������ ��Ŭ�������� ��ã��� �̵�
    if (KEYMANAGER->KeyDown(VK_RBUTTON))
    {
        //from (ĳ����) to (���콺)
        Int2 from;
        Int2 to;
        bool isFind =
            Tm->VectorToIdx(Pl->Getbody()->Position, from);
        isFind &= Tm->VectorToIdx(g_Mouse, to);
        if (isFind)
        {
            //��ã�⸦ �ض�
            if (Tm->PathFinding(from, to, Pl->GetWay()))
            {
                //ù ��� ,������ ����
                Pl->Setfrom(Pl->Getbody()->Position);
                Pl->GetWay().pop_back();
                Pl->Setto(Pl->GetWay().back()->img->Position);
                Pl->Setg(0.0f);
            }
        }

    }






    //ĳ���Ͱ� �����̰� ���Ŀ�
    //ī�޶� �����̱�
    CAMMANAGER->Pos = Pl->Getbody()->Position - Vector2(WINSIZEX*0.5f, WINSIZEY * 0.5f);

    Saturate(CAMMANAGER->Pos.x, Tm->LB.x, Tm->RT.x - WINSIZEX);
    Saturate(CAMMANAGER->Pos.y, Tm->LB.y, Tm->RT.y - WINSIZEY);

    Pl->LateUpdate();
    Mon->LateUpdate();
    Tm->LateUpdate();
}

void Scene2::Render()
{
    Tm->Render();
    Pl->Render();
    Mon->Render();
}
