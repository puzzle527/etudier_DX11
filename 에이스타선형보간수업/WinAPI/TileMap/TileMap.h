#pragma once
enum TileState
{
    TILE_NONE,
    TILE_WALL,
    TILE_TRAP,
    TILE_DOOR
};
class Tile
{
public:
    Image*  img;
    int     state;      //타일 상태
    UINT    ImgIdx;     //타일이 몇번째 이미지를 쓰고있는가?

    //Astar
    Int2    TileIdx;    //본인이 몇번째 원소인가
    int     F;        //총비용
    int     G;        //현재비용
    int     H;        //예상비용
    Tile*   P;        //누굴통해 갱신되었는가?    
    bool    isFind;   //탐색을 했던 타일인가?
    void    CalcH(Int2 End);//도착예상비용계산
    void    CalcF();//총비용 만들기
};
//                 타일주소,도착예상비용
using PTile = pair<Tile*, int>;

struct compare
{
    //연산자 오버로딩
    bool operator()(PTile& a, PTile& b)
    {
        return a.second > b.second;
    }
};




struct TileImg
{
    _tstring file;
    Int2     MaxFrame;
};
class TileMap
{
private:
    
    //Tile Tiles[10][10];
public:

    vector<TileImg>         Images;
    vector<vector<Tile>>    Tiles;
    Int2                    TileSize;   //갯수
    Vector2                 TileScale;   //타일하나의크기
    Vector2                 LB;   //왼쪽아래모서리점
    Vector2                 RT;   //오른쪽위모서리점
    TileMap();
    ~TileMap();

    HRESULT Init();//초기화

    void InitPosition();
    void InitTiles(Int2 from, Int2 to);
    void DeleteTiles(Int2 from, Int2 to);

    //Vector2 -> TileIdx
    bool VectorToIdx(IN Vector2 pt, OUT Int2& Idx);
    


    void Release();//해제

    void Update();//갱신
    void LateUpdate();//늦은갱신
    void Render();//그리기
    void Save(string file);
    void Load(string file);

    //길찾기 함수
    bool PathFinding(Int2 from, Int2 to,
        OUT vector<Tile*>& way);
};

