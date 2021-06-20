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
    int     state;      //Ÿ�� ����
    UINT    ImgIdx;     //Ÿ���� ���° �̹����� �����ִ°�?

    //Astar
    Int2    TileIdx;    //������ ���° �����ΰ�
    int     F;        //�Ѻ��
    int     G;        //������
    int     H;        //������
    Tile*   P;        //�������� ���ŵǾ��°�?    
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
class TileMap
{
private:
    
    //Tile Tiles[10][10];
public:

    vector<TileImg>         Images;
    vector<vector<Tile>>    Tiles;
    Int2                    TileSize;   //����
    Vector2                 TileScale;   //Ÿ���ϳ���ũ��
    Vector2                 LB;   //���ʾƷ��𼭸���
    Vector2                 RT;   //���������𼭸���
    TileMap();
    ~TileMap();

    HRESULT Init();//�ʱ�ȭ

    void InitPosition();
    void InitTiles(Int2 from, Int2 to);
    void DeleteTiles(Int2 from, Int2 to);

    //Vector2 -> TileIdx
    bool VectorToIdx(IN Vector2 pt, OUT Int2& Idx);
    


    void Release();//����

    void Update();//����
    void LateUpdate();//��������
    void Render();//�׸���
    void Save(string file);
    void Load(string file);

    //��ã�� �Լ�
    bool PathFinding(Int2 from, Int2 to,
        OUT vector<Tile*>& way);
};

