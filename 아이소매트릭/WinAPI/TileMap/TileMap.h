#pragma once

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

