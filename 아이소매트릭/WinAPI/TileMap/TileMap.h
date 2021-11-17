#pragma once

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

