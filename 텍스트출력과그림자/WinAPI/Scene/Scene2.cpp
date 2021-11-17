#include "stdafx.h"
#include "Scene2.h"
#include "Player\Player.h"
#include "Player\Monster.h"
#include "TileMap\IsoTileMap.h"

Scene2::Scene2()
{
    Tm = new IsoTileMap();
    TileImg temp;
    //0번 타일 추가
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
    //캐릭터가 움직이고 난후에
    // 발위치의 타일맵 상태비교
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
    //유저가 우클릭했을때 길찾기로 이동
    if (KEYMANAGER->KeyDown(VK_RBUTTON))
    {
        //from (캐릭터) to (마우스)
        Int2 from;
        Int2 to;
        bool isFind =
            Tm->VectorToIdx(Pl->Getbody()->Position, from);
        isFind &= Tm->VectorToIdx(g_Mouse, to);
        if (isFind)
        {
            //길찾기를 해라
            if (Tm->PathFinding(from, to, Pl->GetWay()))
            {
                //첫 출발 ,목적지 세팅
                Pl->Setfrom(Pl->Getbody()->Position + Vector2(0,40.0f));
                Pl->GetWay().pop_back();
                Pl->Setto(Pl->GetWay().back()->img->Position + Vector2(0, 40.0f));
                Pl->Setg(0.0f);
            }
        }

    }






    //캐릭터가 움직이고 난후에
    //카메라 움직이기
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
    //배경색
    //SetBkColor(g_hdc, RGB(255, 0, 0));

    //텍스트색
    SetTextColor(g_hdc, RGB(255, 0, 0));

    //폰트생성
    HFONT ft
        = CreateFontA(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET,
            0, 0, 0, VARIABLE_PITCH | FF_ROMAN, "나눔고딕");
    HFONT old = (HFONT)SelectObject(g_hdc, ft);



    //Rectangle(g_hdc, 100, 100, 200, 200);
    //1바이트 문자열
    string str = "Player";

    //g_Mouse.x = (float)LOWORD(lParam) + CAMMANAGER->Pos.x;
    //g_Mouse.y = (float)WINSIZEY - (float)HIWORD(lParam) + CAMMANAGER->Pos.y;


    Vector2 CharScreenPos = Pl->Getbody()->Position;
    CharScreenPos -= CAMMANAGER->Pos;
    CharScreenPos.y = (float)WINSIZEY - CharScreenPos.y;

    //캐릭터 가운데위치에서 원하는위치로 이동
    CharScreenPos -= Vector2(50, 70);


    TextOutA(g_hdc, CharScreenPos.x,
        CharScreenPos.y, str.c_str(), str.size());


    //2바이트 문자열
    //TextOutW()

    SelectObject(g_hdc, old);
    DeleteObject(ft);

}
