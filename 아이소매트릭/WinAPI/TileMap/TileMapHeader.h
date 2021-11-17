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
    int     state;      //Ÿ�� ����
    UINT    ImgIdx;     //Ÿ���� ���° �̹����� �����ִ°�?

    //Astar
    Int2    TileIdx;    //������ ���° �����ΰ�
    int     F;        //�Ѻ��
    int     G;        //������
    int     H;        //������
    Tile* P;        //�������� ���ŵǾ��°�?    
    bool    isFind;   //Ž���� �ߴ� Ÿ���ΰ�?
    void    CalcH(Int2 End);//������������
    void    CalcF();//�Ѻ�� �����
};
//                 Ÿ���ּ�,����������
using PTile = pair<Tile*, int>;

struct compare
{
    //������ �����ε�
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