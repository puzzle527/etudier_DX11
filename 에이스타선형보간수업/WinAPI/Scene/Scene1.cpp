#include "stdafx.h"
#include "Scene1.h"
#include "TileMap\TileMap.h"

//������ ����� (��Ű��,���巯��)

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


    

    //0�� Ÿ�� �߰�
    temp.file = _T("Tile.png");
    temp.MaxFrame = Int2(8, 6);
    Tm->Images.push_back(temp);
    //1�� Ÿ���߰�
    temp.file = _T("Tile2.png");
    temp.MaxFrame = Int2(11, 7);
    Tm->Images.push_back(temp);


    Tm->Init();

    //������ =   Ÿ�ϸ�
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
    //Ÿ�� ������ġ
    if (ImGui::SliderFloat2("LB", Tm->LB,
        -1000, 1000))
    {
        Tm->InitPosition();
    }
    //Ÿ�� �Ѱ� ������
    if (ImGui::SliderFloat2("TileScale",
        Tm->TileScale, 0, 500))
    {
        Tm->InitPosition();
    }
    //���μ��� Ÿ�� ����
    if (ImGui::InputInt("TileSizeX", &TileSize.x))
    {
        //�÷�����
        if (TileSize.x > Tm->TileSize.x)
        {
            //�迭������1����
            Tm->Tiles.emplace_back();
            //�þ �迭�� �����ŭ �迭 �߰�
            Tm->Tiles[Tm->TileSize.x].resize(Tm->TileSize.y);
            //���λ��� Ÿ�� ����� �ʱ�ȭ
            Tm->InitTiles(Int2(Tm->TileSize.x, 0),
                Int2(Tm->TileSize.x + 1, Tm->TileSize.y));
            //�ٲٷ��°� �ֱ�
            Tm->TileSize.x = TileSize.x;
            Tm->InitPosition();
        }
        //�ٿ�����
        else
        {
            //�����Ҵ� ���ִ� �̹��� ����
            Tm->DeleteTiles(Int2(Tm->TileSize.x - 1, 0),
                Int2(Tm->TileSize.x, Tm->TileSize.y));

            Tm->Tiles[Tm->TileSize.x - 1].clear();
            Tm->Tiles[Tm->TileSize.x - 1].shrink_to_fit();

            //�ϳ�����
            Tm->Tiles.pop_back();
            //�ٲٷ��°� �ֱ�
            Tm->TileSize.x = TileSize.x;

        }
    }
    if (ImGui::InputInt("TileSizeY", &TileSize.y))
    {
        //�÷����Ҷ�
        if (TileSize.y > Tm->TileSize.y)
        {
            for (int i = 0; i < TileSize.x; i++)
            {
                Tm->Tiles[i].emplace_back();
            }
            Tm->InitTiles(Int2(0, Tm->TileSize.y),
                Int2(Tm->TileSize.x, Tm->TileSize.y + 1));
            //�ٲٷ��°� �ֱ�
            Tm->TileSize.y = TileSize.y;
            Tm->InitPosition();
        }
        //�ٿ����Ҷ�
        else
        {
            Tm->DeleteTiles(Int2(0, Tm->TileSize.y - 1),
                Int2(Tm->TileSize.x, Tm->TileSize.y));

            for (int i = 0; i < TileSize.x; i++)
            {
                Tm->Tiles[i].pop_back();
            }
            //�ٲٷ��°� �ֱ�
            Tm->TileSize.y = TileSize.y;
        }
    }

}

void Scene1::TileImgButton()
{
    int tempIdx = ImgIdx;
    //�̹��� �ѱ��
    if (ImGui::InputInt("ImgIdx", &tempIdx))
    {
        if (tempIdx > (int)Tm->Images.size() - 1)
        {
            ImgIdx = 0; //ù��°�̹����� ������
        }
        else if (tempIdx < 0)
        {
            //������ �̹����� ������
            ImgIdx = Tm->Images.size() - 1;
        }
        else
        {
            ImgIdx = tempIdx;
        }
    }

    Int2 MF = Tm->Images[ImgIdx].MaxFrame;
    ImVec2 size;
    // 300x 300�ȿ� �̹���������ŭ ������
    size.x = 300.0f / (float)MF.x;
    size.y = 300.0f / (float)MF.y;

    //�ؽ��� ��ǥ
    ImVec2 LT, RB;
    int index = 0;
    for (UINT i = 0; i < MF.y; i++)
    {
        for (UINT j = 0; j < MF.x; j++)
        {
            if (j != 0)
            {
                //�����ٿ� ��ġ
                ImGui::SameLine();
            }
            //�ؽ��� ��ǥ
            LT.x = 1.0f / MF.x * j;
            LT.y = 1.0f / MF.y * i;
            RB.x = 1.0f / MF.x * (j + 1);
            RB.y = 1.0f / MF.y * (i + 1);

            ID3D11ShaderResourceView* srv =
                RESOURCEMANAGER->LoadTexture(Tm->Images[ImgIdx].file);
            //�̰��־�� ��ư�� ���� ����
            ImGui::PushID(index);
            //������ �̹�����ư
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
    //Ÿ�� ���°�
    ImGui::SliderInt("TileState",
        &State, TILE_NONE, TILE_DOOR);

    //���콺�� ImGui â ���� ������
    ImVec2 min = ImGui::GetWindowPos();
    ImVec2 max;
    max.x = min.x + ImGui::GetWindowSize().x;
    max.y = min.y + ImGui::GetWindowSize().y;
    //Imguiâ ���� ������
    if (!ImGui::IsMouseHoveringRect(min, max))
    {
        //��Ŭ���� ������������ �귯�÷� ĥ�ϱ�
        if (KEYMANAGER->KeyPress(VK_LBUTTON))
        {
            Int2 idx;
            //Ÿ�ϸ� �ȿ� ������
            if (Tm->VectorToIdx(g_Mouse, idx))
            {
                //�ٲ��� �̹���
                Image* Target =
                    Tm->Tiles[idx.x][idx.y].img;
                Target->Frame = Frame;
                //�ٲٷ��� �̹����� ���� �̹����� �ٸ���
                if (ImgIdx != Tm->Tiles[idx.x][idx.y].ImgIdx)
                {
                    Target->ChageImage(Tm->Images[ImgIdx].file,
                        Tm->Images[ImgIdx].MaxFrame);
                    Tm->Tiles[idx.x][idx.y].ImgIdx = ImgIdx;
                }
                Tm->Tiles[idx.x][idx.y].state = State;
                //����׿� Ÿ�� ��
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
