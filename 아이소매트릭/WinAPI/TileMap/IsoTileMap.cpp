#include "stdafx.h"
#include "IsoTileMap.h"

IsoTileMap::IsoTileMap()
{
    //�⺻ Ÿ�ϸ� ����
    TileSize = Int2(10, 10);

    TileScale.y = 50.0f;
    TileScale.x = 50.0f * sqrt3;

    B = Vector2(0.0f, 0.0f);
    Vector2 halfScale = TileScale * 0.5f;
    T.x = B.x + (TileSize.x - TileSize.y) * halfScale.x;
    T.y = B.y + (TileSize.x + TileSize.y) * halfScale.x;

    Tiles.resize(TileSize.x);
    for (int i = 0; i < TileSize.x; i++)
    {
        Tiles[i].resize(TileSize.y);
    }
}

IsoTileMap::~IsoTileMap()
{
    DeleteTiles(Int2(0, 0), TileSize);
}

HRESULT IsoTileMap::Init()
{
    InitTiles(Int2(0, 0), TileSize);
    InitPosition();
    return false;
}

void IsoTileMap::Update()
{
}

void IsoTileMap::LateUpdate()
{
}

void IsoTileMap::Render()
{
    for (int i = TileSize.x - 1; i >= 0; i--)
    {
        for (int j = TileSize.y - 1; j >= 0; j--)
        {
            Tiles[i][j].img->Render();
        }
    }
}

void IsoTileMap::InitTiles(Int2 from, Int2 to)
{
    for (int i = from.x; i < to.x; i++)
    {
        for (int j = from.y; j < to.y; j++)
        {
            Tiles[i][j].state = TILE_NONE;
            Tiles[i][j].img
                = new Image(Images[0].file);
            Tiles[i][j].img->Init();
            Tiles[i][j].img->MaxFrame
                = Images[0].MaxFrame;
            Tiles[i][j].img->WorldUpdate();
            Tiles[i][j].ImgIdx = 0;
        }
    }
}

void IsoTileMap::InitPosition()
{
    Vector2 halfScale = TileScale * 0.5f;
    for (int i = 0; i < TileSize.x; i++)
    {
        for (int j = 0; j < TileSize.y; j++)
        {
            Tiles[i][j].TileIdx = Int2(i, j);
            Tiles[i][j].img->Scale.x =
                TileScale.x;
            Tiles[i][j].img->Scale.y =
                TileScale.y * 2.0f;
            Tiles[i][j].img->Position.x
                = B.x + (i - j) * halfScale.x;
            Tiles[i][j].img->Position.y
                = B.y + (i + j) * halfScale.y;
            Tiles[i][j].img->WorldUpdate();
        }
    }
    T.x = B.x + (TileSize.x - TileSize.y) * halfScale.x;
    T.y = B.y + (TileSize.x + TileSize.y) * halfScale.x;
}

void IsoTileMap::DeleteTiles(Int2 from, Int2 to)
{
    for (int i = from.x; i < to.x; i++)
    {
        for (int j = from.y; j < to.y; j++)
        {
            delete Tiles[i][j].img;
        }
    }
}

bool IsoTileMap::VectorToIdx(IN Vector2 pt, OUT Int2& Idx)
{

    //Ÿ���� �̵��� ��ǥ ����
    pt -= B;
    //Ÿ�� �����Ϸ� ��ǥ ������
    pt.x /= TileScale.x; //-> (i-j)/2
    pt.y /= TileScale.y; //-> (i+j)/2

    //����������
    Idx.x = (int)(pt.x + pt.y);
    Idx.y = (int)(pt.y - pt.x);

    bool isCollision =
        (0 <= Idx.x && Idx.x < TileSize.x &&
            0 <= Idx.y && Idx.y < TileSize.y) ? true : false;

    return isCollision;
}

void IsoTileMap::Save(string file)
{
    ofstream fout;
    fout.open(file.c_str(), ios::out);
    if (fout.is_open())
    {
        //' '; '\n'; '\t'; �о�ö� ���⼭ ���� �о�´�
        fout << TileSize.x << ' ' << TileSize.y << endl;
        fout << TileScale.x << ' ' << TileScale.y << endl;
        fout << B.x << ' ' << B.y << endl;

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

void IsoTileMap::Load(string file)
{
    ifstream fin;
    fin.open(file, ios::in);
    if (fin.is_open())
    {
        //��������ִ� ���� ����
        DeleteTiles(Int2(0, 0), TileSize);
        for (int i = 0; i < TileSize.x; i++)
        {
            Tiles[i].clear();
        }
        Tiles.clear();



        fin >> TileSize.x >> TileSize.y;
        fin >> TileScale.x >> TileScale.y;
        fin >> B.x >> B.y;


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
                //�⺻ 0 ���� �ƴ� �ٸ��̹����� ����ϴ°��
                int ImgIdx;
                fin >> ImgIdx;
                if (Tiles[i][j].ImgIdx != ImgIdx)
                {
                    Tiles[i][j].img->ChageImage(Images[ImgIdx].file,
                        Images[ImgIdx].MaxFrame);
                    Tiles[i][j].ImgIdx = ImgIdx;
                }


                fin >> Tiles[i][j].state;
                fin >> Tiles[i][j].img->Frame.x >>
                    Tiles[i][j].img->Frame.y;

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

bool IsoTileMap::PathFinding(Int2 from, Int2 to, OUT vector<Tile*>& way)
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

    //������� �켱����ť�� Ǫ��
    Tile* pTemp = &Tiles[from.x][from.y];
    pTemp->G = 0;//����� �������� 0
    pTemp->CalcH(to);//������ �����
    pTemp->CalcF(); //�Ѻ�� �����
    List.push({ pTemp,pTemp->F });

    //����Ʈ�� ��ų� ���������� ã�������� �ݺ�
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

        //�밢��4��
    }

    //�������� ������ �Ǿ�����

    Tile* p = &Tiles[to.x][to.y];

    //to 3,3  -> 3,2 -> 3,1
    while (1)
    {
        way.push_back(p);
        p = p->P;
        if (p == nullptr)
        {
            break;
        }
    }
    return true;
}
