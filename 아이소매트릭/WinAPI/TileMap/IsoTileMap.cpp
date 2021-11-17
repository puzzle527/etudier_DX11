#include "stdafx.h"
#include "IsoTileMap.h"

IsoTileMap::IsoTileMap()
{
    //기본 타일맵 생성
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

    //타일이 이동한 좌표 제외
    pt -= B;
    //타일 스케일로 좌표 나누기
    pt.x /= TileScale.x; //-> (i-j)/2
    pt.y /= TileScale.y; //-> (i+j)/2

    //연립방정식
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
        //' '; '\n'; '\t'; 읽어올때 여기서 끊고 읽어온다
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
        //원래들고있던 벡터 해제
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
                //기본 0 값이 아닌 다른이미지를 사용하는경우
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

                //디버그용
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
    //둘중에 하나가 벽이면 갈 수 있는길이 없다.
    if (Tiles[to.x][to.y].state == TILE_WALL ||
        Tiles[from.x][from.y].state == TILE_WALL)
    {
        return false;
    }

    //기존에 있던 길은 전부 비운다.
    way.clear();
    //출발지 목적지 같으면
    if (to == from)
    {
        return false;//제자리 멈추기
    }

    //타일 비용 초기화
    for (int i = 0; i < TileSize.x; i++)
    {
        for (int j = 0; j < TileSize.y; j++)
        {
            //최대값 초기화
            Tiles[i][j].F = INT_MAX;
            Tiles[i][j].G = INT_MAX;
            Tiles[i][j].H = INT_MAX;
            Tiles[i][j].P = nullptr;
            Tiles[i][j].isFind = false;
        }
    }

    //탐색리스트
     //           원소타입,컨테이너타입
    priority_queue<PTile, vector<PTile>, compare> List;

    //출발지를 우선순위큐에 푸시
    Tile* pTemp = &Tiles[from.x][from.y];
    pTemp->G = 0;//출발지 현재비용은 0
    pTemp->CalcH(to);//예상비용 만들기
    pTemp->CalcF(); //총비용 만들기
    List.push({ pTemp,pTemp->F });

    //리스트가 비거나 도착지점을 찾을때까지 반복
    while (1)
    {
        //탐색리스트가 비면 false 반환
        if (List.empty())
        {
            return false;
        }
        //탐색노드 받아오기
        PTile Temp = List.top();
        //탐색목록에서 제외
        Temp.first->isFind = true;
        //맨윗값 빼버리기
        List.pop();

        //맨윗값이 도착점이면 종료(길찾기 종료조건)
        if (Temp.first->TileIdx == to)
        {
            break;
        }
        //인접 타일 비용검사
        vector<Int2> LoopIdx;

        //왼쪽벽이 존재할때
        if (Temp.first->TileIdx.x > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->TileIdx.x - 1,
                Temp.first->TileIdx.y));
        }
        //위쪽벽이 존재할때
        if (Temp.first->TileIdx.y > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->TileIdx.x,
                Temp.first->TileIdx.y - 1));
        }
        //오른쪽벽이 존재할때
        if (Temp.first->TileIdx.x < TileSize.x - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->TileIdx.x + 1,
                Temp.first->TileIdx.y));
        }
        //아래쪽벽이 존재할때
        if (Temp.first->TileIdx.y < TileSize.y - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->TileIdx.x,
                Temp.first->TileIdx.y + 1));
        }

        //대각선 스킵
        //4방향 인덱스만큼 반복
        for (int i = 0; i < LoopIdx.size(); i++)
        {
            Tile* loop =
                &Tiles[LoopIdx[i].x][LoopIdx[i].y];
            //벽이 아닐때
            if (loop->state != TILE_WALL)
            {
                //예상비용 만들기
                loop->CalcH(to);
                //현재 가지고있는 비용이 클때
                if (loop->G > Temp.first->G + 10)
                {
                    //비용갱신
                    loop->G = Temp.first->G + 10;
                    loop->CalcF();
                    loop->P = Temp.first;
                    //이 타일이 찾은적 없던 타일이면 리스트에 추가
                    if (!loop->isFind)
                    {
                        List.push({ loop,loop->F });
                    }
                }
            }
        }
        LoopIdx.clear();

        //대각선4개
    }

    //도착지가 설정이 되었을때

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
