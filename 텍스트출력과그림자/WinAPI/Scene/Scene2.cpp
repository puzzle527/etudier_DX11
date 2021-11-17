#include "stdafx.h"
#include "Scene2.h"
#include "Player\Player.h"
#include "Player\Monster.h"
#include "TileMap\IsoTileMap.h"

Scene2::Scene2()
{
    Tm = new IsoTileMap();
    TileImg temp;
    //0�� Ÿ�� �߰�
    temp.file = _T("iso.png");
    temp.MaxFrame = Int2(8, 7);
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
                Pl->Setfrom(Pl->Getbody()->Position + Vector2(0,40.0f));
                Pl->GetWay().pop_back();
                Pl->Setto(Pl->GetWay().back()->img->Position + Vector2(0, 40.0f));
                Pl->Setg(0.0f);
            }
        }

    }






    //ĳ���Ͱ� �����̰� ���Ŀ�
    //ī�޶� �����̱�
    CAMMANAGER->Pos = Pl->Getbody()->Position - Vector2(WINSIZEX*0.5f, WINSIZEY * 0.5f);

    //Saturate(CAMMANAGER->Pos.x, Tm->LB.x, Tm->RT.x - WINSIZEX);
    //Saturate(CAMMANAGER->Pos.y, Tm->LB.y, Tm->RT.y - WINSIZEY);

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

void Scene2::TextRender()
{
    //����
    //SetBkColor(g_hdc, RGB(255, 0, 0));

    //�ؽ�Ʈ��
    SetTextColor(g_hdc, RGB(255, 0, 0));

    //��Ʈ����
    HFONT ft
        = CreateFontA(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET,
            0, 0, 0, VARIABLE_PITCH | FF_ROMAN, "�������");
    HFONT old = (HFONT)SelectObject(g_hdc, ft);



    //Rectangle(g_hdc, 100, 100, 200, 200);
    //1����Ʈ ���ڿ�
    string str = "Player";

    //g_Mouse.x = (float)LOWORD(lParam) + CAMMANAGER->Pos.x;
    //g_Mouse.y = (float)WINSIZEY - (float)HIWORD(lParam) + CAMMANAGER->Pos.y;


    Vector2 CharScreenPos = Pl->Getbody()->Position;
    CharScreenPos -= CAMMANAGER->Pos;
    CharScreenPos.y = (float)WINSIZEY - CharScreenPos.y;

    //ĳ���� �����ġ���� ���ϴ���ġ�� �̵�
    CharScreenPos -= Vector2(50, 70);


    TextOutA(g_hdc, CharScreenPos.x,
        CharScreenPos.y, str.c_str(), str.size());


    //2����Ʈ ���ڿ�
    //TextOutW()

    SelectObject(g_hdc, old);
    DeleteObject(ft);

}
