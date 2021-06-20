#include "stdafx.h"
#include "Scene1.h"
#include "TileMap\TileMap.h"

//런게임 만들기 (쿠키런,윈드러너)

Scene1::Scene1()
{

    /*TileImg temp;
    temp.file = _T("Tile.png");
    temp.MaxFrame = Int2(8, 6);
    Images.push_back(temp);
    temp.file = _T("Tile2.png");
    temp.MaxFrame = Int2(11, 7);
    Images.push_back(temp);*/

    Tm = new TileMap();
    TileImg temp;


    

    //0번 타일 추가
    temp.file = _T("Tile.png");
    temp.MaxFrame = Int2(8, 6);
    Tm->Images.push_back(temp);
    //1번 타일추가
    temp.file = _T("Tile2.png");
    temp.MaxFrame = Int2(11, 7);
    Tm->Images.push_back(temp);


    Tm->Init();

    //에디터 =   타일맵
    TileSize = Tm->TileSize;

    ImgIdx = 0;
    State = TILE_NONE;
    Frame = Int2(0, 0);
}

Scene1::~Scene1()
{
    delete Tm;
}

HRESULT Scene1::Init()
{

    return S_OK;
}

void Scene1::Release()
{

}

void Scene1::Update()
{
    //cam move
    if (KEYMANAGER->KeyPress('W'))
    {
        CAMMANAGER->Pos += UP * 300.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('S'))
    {
        CAMMANAGER->Pos += DOWN * 300.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('A'))
    {
        CAMMANAGER->Pos += LEFT * 300.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('D'))
    {
        CAMMANAGER->Pos += RIGHT * 300.0f * DeltaTime;
    }

    ResizeButton();
    TileImgButton();
    TileBrush();

    if (ImGui::Button("save"))
    {
        Tm->Save("Save/map1.txt");
    }
    ImGui::SameLine();
    if (ImGui::Button("load"))
    {
        Tm->Load("Save/map1.txt");
    }


}

void Scene1::LateUpdate()
{
}

void Scene1::Render()
{
    Tm->Render();
}

void Scene1::ResizeButton()
{
    //타일 시작위치
    if (ImGui::SliderFloat2("LB", Tm->LB,
        -1000, 1000))
    {
        Tm->InitPosition();
    }
    //타일 한개 사이즈
    if (ImGui::SliderFloat2("TileScale",
        Tm->TileScale, 0, 500))
    {
        Tm->InitPosition();
    }
    //가로세로 타일 갯수
    if (ImGui::InputInt("TileSizeX", &TileSize.x))
    {
        //늘려야함
        if (TileSize.x > Tm->TileSize.x)
        {
            //배열사이즈1증가
            Tm->Tiles.emplace_back();
            //늘어난 배열에 사이즈만큼 배열 추가
            Tm->Tiles[Tm->TileSize.x].resize(Tm->TileSize.y);
            //새로생긴 타일 멤버값 초기화
            Tm->InitTiles(Int2(Tm->TileSize.x, 0),
                Int2(Tm->TileSize.x + 1, Tm->TileSize.y));
            //바꾸려는값 넣기
            Tm->TileSize.x = TileSize.x;
            Tm->InitPosition();
        }
        //줄여야함
        else
        {
            //동적할당 되있는 이미지 해제
            Tm->DeleteTiles(Int2(Tm->TileSize.x - 1, 0),
                Int2(Tm->TileSize.x, Tm->TileSize.y));

            Tm->Tiles[Tm->TileSize.x - 1].clear();
            Tm->Tiles[Tm->TileSize.x - 1].shrink_to_fit();

            //하나빼기
            Tm->Tiles.pop_back();
            //바꾸려는값 넣기
            Tm->TileSize.x = TileSize.x;

        }
    }
    if (ImGui::InputInt("TileSizeY", &TileSize.y))
    {
        //늘려야할때
        if (TileSize.y > Tm->TileSize.y)
        {
            for (int i = 0; i < TileSize.x; i++)
            {
                Tm->Tiles[i].emplace_back();
            }
            Tm->InitTiles(Int2(0, Tm->TileSize.y),
                Int2(Tm->TileSize.x, Tm->TileSize.y + 1));
            //바꾸려는값 넣기
            Tm->TileSize.y = TileSize.y;
            Tm->InitPosition();
        }
        //줄여야할때
        else
        {
            Tm->DeleteTiles(Int2(0, Tm->TileSize.y - 1),
                Int2(Tm->TileSize.x, Tm->TileSize.y));

            for (int i = 0; i < TileSize.x; i++)
            {
                Tm->Tiles[i].pop_back();
            }
            //바꾸려는값 넣기
            Tm->TileSize.y = TileSize.y;
        }
    }

}

void Scene1::TileImgButton()
{
    int tempIdx = ImgIdx;
    //이미지 넘기기
    if (ImGui::InputInt("ImgIdx", &tempIdx))
    {
        if (tempIdx > (int)Tm->Images.size() - 1)
        {
            ImgIdx = 0; //첫번째이미지로 돌리기
        }
        else if (tempIdx < 0)
        {
            //마지막 이미지로 돌리기
            ImgIdx = Tm->Images.size() - 1;
        }
        else
        {
            ImgIdx = tempIdx;
        }
    }

    Int2 MF = Tm->Images[ImgIdx].MaxFrame;
    ImVec2 size;
    // 300x 300안에 이미지갯수만큼 나누기
    size.x = 300.0f / (float)MF.x;
    size.y = 300.0f / (float)MF.y;

    //텍스쳐 좌표
    ImVec2 LT, RB;
    int index = 0;
    for (UINT i = 0; i < MF.y; i++)
    {
        for (UINT j = 0; j < MF.x; j++)
        {
            if (j != 0)
            {
                //같은줄에 배치
                ImGui::SameLine();
            }
            //텍스쳐 좌표
            LT.x = 1.0f / MF.x * j;
            LT.y = 1.0f / MF.y * i;
            RB.x = 1.0f / MF.x * (j + 1);
            RB.y = 1.0f / MF.y * (i + 1);

            ID3D11ShaderResourceView* srv =
                RESOURCEMANAGER->LoadTexture(Tm->Images[ImgIdx].file);
            //이게있어야 버튼이 각자 눌림
            ImGui::PushID(index);
            //눌리는 이미지버튼
            if (ImGui::ImageButton((void*)srv, size, LT, RB))
            {
                /*ImgIdx.x = j;
                ImgIdx.y = i;*/
                //cout << j << "," << i << endl;
                Frame = Int2(j, i);
            }
            index++;
            ImGui::PopID();
        }
    }



}

void Scene1::TileBrush()
{
    //타일 상태값
    ImGui::SliderInt("TileState",
        &State, TILE_NONE, TILE_DOOR);

    //마우스가 ImGui 창 위에 없을때
    ImVec2 min = ImGui::GetWindowPos();
    ImVec2 max;
    max.x = min.x + ImGui::GetWindowSize().x;
    max.y = min.y + ImGui::GetWindowSize().y;
    //Imgui창 위에 없을때
    if (!ImGui::IsMouseHoveringRect(min, max))
    {
        //좌클릭을 누르고있으면 브러시로 칠하기
        if (KEYMANAGER->KeyPress(VK_LBUTTON))
        {
            Int2 idx;
            //타일맵 안에 있을때
            if (Tm->VectorToIdx(g_Mouse, idx))
            {
                //바꿔줄 이미지
                Image* Target =
                    Tm->Tiles[idx.x][idx.y].img;
                Target->Frame = Frame;
                //바꾸려는 이미지가 현재 이미지랑 다를때
                if (ImgIdx != Tm->Tiles[idx.x][idx.y].ImgIdx)
                {
                    Target->ChageImage(Tm->Images[ImgIdx].file,
                        Tm->Images[ImgIdx].MaxFrame);
                    Tm->Tiles[idx.x][idx.y].ImgIdx = ImgIdx;
                }
                Tm->Tiles[idx.x][idx.y].state = State;
                //디버그용 타일 색
                if (State == TILE_WALL)
                {
                    Target->color = Color(0.8f, 0.5f, 0.5f, 0.5f);
                }
                else
                {
                    Target->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
                }

            }

        }


    }
}
