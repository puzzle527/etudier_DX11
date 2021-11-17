#pragma once
#define sqrt3 1.73205f
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
    Image* img;
    int     state;      //타일 상태
    UINT    ImgIdx;     //타일이 몇번째 이미지를 쓰고있는가?

    //Astar
    Int2    TileIdx;    //본인이 몇번째 원소인가
    int     F;        //총비용
    int     G;        //현재비용
    int     H;        //예상비용
    Tile* P;        //누굴통해 갱신되었는가?    
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