#include "stdafx.h"
#include "TileMap.h"

//Ÿ�ϸ� �����ÿ� ó�� ������
TileMap::TileMap()
{
   
    TileSize = Int2(10, 10);
    TileScale = Vector2(50.0f, 50.0f);
    LB = Vector2(0.0f, 0.0f);
    
    Tiles.resize(TileSize.x);
    for (int i = 0; i < TileSize.x; i++)
    {
        Tiles[i].resize(TileSize.y);
    }
}

TileMap::~TileMap()
{
    DeleteTiles(Int2(0, 0), TileSize);
}

HRESULT TileMap::Init()
{
    InitTiles(Int2(0,0), TileSize);
    InitPosition();
    return S_OK;
}

void TileMap::InitPosition()
{
    for (int i = 0; i < TileSize.x; i++)
    {
        for (int j = 0; j < TileSize.y; j++)
        {
            Tiles[i][j].img->Scale = TileScale;
            Tiles[i][j].img->Position
                = LB + Vector2((i + 0.5f) * TileScale.x, (j + 0.5f) * TileScale.y);
            Tiles[i][j].img->WorldUpdate();
        }
    }
    //�ٲ� LB������ �ٽ� ���
    RT.x = LB.x + TileSize.x * TileScale.x;
    RT.y = LB.y + TileSize.y * TileScale.y;
}

void TileMap::InitTiles(Int2 from, Int2 to)
{
    for (int i = from.x; i < to.x; i++)
    {
        for (int j = from.y; j < to.y; j++)
        {
            Tiles[i][j].state = TILE_NONE;
            Tiles[i][j].img = new Image(Images[0].file);
            Tiles[i][j].img->Init();
            Tiles[i][j].img->MaxFrame = Images[0].MaxFrame;

            Tiles[i][j].TileIdx = Int2(i, j);
            Tiles[i][j].ImgIdx = 0;
        }
    }
}

void TileMap::DeleteTiles(Int2 from, Int2 to)
{
    for (int i = from.x; i < to.x; i++)
    {
        for (int j = from.y; j < to.y; j++)
        {
            delete Tiles[i][j].img;
        }
    }
}

bool TileMap::VectorToIdx(IN Vector2 pt,
    OUT Int2& Idx)
{
    bool isCollision =
        (LB.x < pt.x && pt.x < RT.x &&
            LB.y < pt.y && pt.y < RT.y) ? true : false;

    pt -= LB;

    //Ÿ�� �����ϸ�ŭ ������ ��ǥ�� ��ȯ
    Idx.x = (int)(pt.x / TileScale.x);
    Idx.y = (int)(pt.y / TileScale.y);

    return isCollision;
}


void TileMap::Release()
{
}

void TileMap::Update()
{
}

void TileMap::LateUpdate()
{
}

void TileMap::Render()
{
    //â�� ���� ������ǥ
    Vector2 WinRT = CAMMANAGER->Pos +
        Vector2(WINSIZEX, WINSIZEY);
    //�ּ� �ε���
    Int2 Min;
    VectorToIdx(CAMMANAGER->Pos, Min);
    Int2 Max;
    VectorToIdx(WinRT, Max);

    Saturate(Min.x, 0, TileSize.x - 1);
    Saturate(Max.x, 0, TileSize.x - 1);
    Saturate(Min.y, 0, TileSize.y - 1);
    Saturate(Max.y, 0, TileSize.y - 1);

    for (int i = Min.x; i <= Max.x; i++)
    {
        for (int j = Min.y; j <= Max.y; j++)
        {
            Tiles[i][j].img->Render();
        }
    }
}

void TileMap::Save(string file)
{
    //c_str   string ->const char*
    ofstream fout;
    fout.open(file.c_str(), ios::out);
    if (fout.is_open())
    {
        //'\n'; '\t'; ' ';
        fout << TileSize.x << ' ' << TileSize.y << endl;
        fout << TileScale.x << ' ' << TileScale.y << endl;
        fout << LB.x << ' ' << LB.y << endl;
        for (int i = 0; i < TileSize.x; i++)
        {
            for (int j = 0; j < TileSize.y; j++)
            {
                fout << Tiles[i][j].ImgIdx << endl;
                fout << Tiles[i][j].state << endl;
                fout << Tiles[i][j].img->Frame.x << 
                    ' ' << Tiles[i][j].img->Frame.y << endl;
            }
        }

        fout.close();
    }

}

void TileMap::Load(string file)
{
    ifstream fin;
    fin.open(file.c_str(), ios::in);
    if (fin.is_open())
    {
        DeleteTiles(Int2(0, 0), TileSize);
        for (int i = 0; i < TileSize.x; i++)
        {
            Tiles[i].clear();
        }
        Tiles.clear();

        fin >> TileSize.x >> TileSize.y;
        fin >> TileScale.x >> TileScale.y;
        fin >> LB.x >> LB.y;

        Tiles.resize(TileSize.x);
        for (int i = 0; i < TileSize.x; i++)
        {
            Tiles[i].resize(TileSize.y);
        }

        InitTiles(Int2(0, 0), TileSize);

        for (int i = 0; i < TileSize.x; i++)
        {
            for (int j = 0; j < TileSize.y; j++)
            {
                int ImgIdx;
                fin >> ImgIdx;
                if (Tiles[i][j].ImgIdx != ImgIdx)
                {
                    Tiles[i][j].img->ChageImage(Images[ImgIdx].file,
                        Images[ImgIdx].MaxFrame);
                    Tiles[i][j].ImgIdx = ImgIdx;
                }
                fin >> Tiles[i][j].state;

                fin >> Tiles[i][j].img->Frame.x
                    >> Tiles[i][j].img->Frame.y;
                //����׿�
                if (Tiles[i][j].state == TILE_WALL)
                {
                    Tiles[i][j].img->color = Color(0.8f, 0.5f, 0.5f, 0.5f);
                }
                else
                {
                    Tiles[i][j].img->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
                }



            }
        }
        InitPosition();


        fin.close();
    }
}
bool TileMap::PathFinding(Int2 from, Int2 to, OUT vector<Tile*>& way)
{
    //���߿� �ϳ��� ���̸� �� �� �ִ±��� ����.
    if (Tiles[to.x][to.y].state == TILE_WALL ||
        Tiles[from.x][from.y].state == TILE_WALL)
    {
        return false;
    }
    //������ �ִ� ���� ���� ����.
    way.clear();

    //����� ������ ������
    if (to == from)
    {
        return false;//���ڸ� ���߱�
    }

    //Ÿ�� ��� �ʱ�ȭ
    for (int i = 0; i < TileSize.x; i++)
    {
        for (int j = 0; j < TileSize.y; j++)
        {
            //�ִ밪 �ʱ�ȭ
            Tiles[i][j].F = INT_MAX;
            Tiles[i][j].G = INT_MAX;
            Tiles[i][j].H = INT_MAX;
            Tiles[i][j].P = nullptr;
            Tiles[i][j].isFind = false;
        }
    }
    //Ž������Ʈ
    //           ����Ÿ��,�����̳�Ÿ��
    priority_queue<PTile, vector<PTile>, compare> List;
    //priority_queue<int, vector<int>,cmp> List;

    //������� �켱����ť�� Ǫ��
    Tile* pTemp = &Tiles[from.x][from.y];
    pTemp->G = 0;//����� �������� 0
    pTemp->CalcH(to);//������ �����
    pTemp->CalcF(); //�Ѻ�� �����
    List.push({ pTemp,pTemp->F });

    while (1)
    {
        //Ž������Ʈ�� ��� false ��ȯ
        if (List.empty())
        {
            return false;
        }
        //Ž����� �޾ƿ���
        PTile Temp = List.top();
        //Ž����Ͽ��� ����
        Temp.first->isFind = true;
        //������ ��������
        List.pop();

        //�������� �������̸� ����(��ã�� ��������)
        if (Temp.first->TileIdx == to)
        {
            break;
        }

        //���� Ÿ�� ���˻�
        vector<Int2> LoopIdx;

        //���ʺ��� �����Ҷ�
        if (Temp.first->TileIdx.x > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->TileIdx.x - 1,
                Temp.first->TileIdx.y));
        }
        //���ʺ��� �����Ҷ�
        if (Temp.first->TileIdx.y > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->TileIdx.x,
                Temp.first->TileIdx.y - 1));
        }
        //�����ʺ��� �����Ҷ�
        if (Temp.first->TileIdx.x < TileSize.x - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->TileIdx.x + 1,
                Temp.first->TileIdx.y));
        }
        //�Ʒ��ʺ��� �����Ҷ�
        if (Temp.first->TileIdx.y < TileSize.y - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->TileIdx.x,
                Temp.first->TileIdx.y + 1));
        }
        //�밢�� ��ŵ
        //4���� �ε�����ŭ �ݺ�
        for (int i = 0; i < LoopIdx.size(); i++)
        {
            Tile* loop =
                &Tiles[LoopIdx[i].x][LoopIdx[i].y];
            //���� �ƴҶ�
            if (loop->state != TILE_WALL)
            {
                //������ �����
                loop->CalcH(to);
                //���� �������ִ� ����� Ŭ��
                if (loop->G > Temp.first->G + 10)
                {
                    //��밻��
                    loop->G = Temp.first->G + 10;
                    loop->CalcF();
                    loop->P = Temp.first;
                    //�� Ÿ���� ã���� ���� Ÿ���̸� ����Ʈ�� �߰�
                    if (!loop->isFind)
                    {
                        List.push({ loop,loop->F });
                    }
                }
            }
        }
        LoopIdx.clear();
        //�밢�� 4���߰�



    }


    //�������� ������ �Ǿ�����
    Tile* p = &Tiles[to.x][to.y];
    while (1)
    {
        way.push_back(p);
        p = p->P;
        //������
        if (p == nullptr)
        {
            break;
        }
    }
    return true;
}
//3,3   5,5
void Tile::CalcH(Int2 End)
{
    H = (abs(TileIdx.x - End.x) +
        abs(TileIdx.y - End.y)) * 10;
}

void Tile::CalcF()
{
    F = G + H;
}
