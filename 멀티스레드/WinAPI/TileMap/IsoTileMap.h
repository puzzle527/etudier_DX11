#pragma once
class IsoTileMap
{
public:

    vector<TileImg>         Images;
    vector<vector<Tile>>    Tiles;
    Int2                    TileSize;   //����
    Vector2                 TileScale;   //Ÿ���ϳ���ũ��
    Vector2                 B;   //�Ʒ��𼭸���
    Vector2                 T;   //���𼭸���
    IsoTileMap();
    ~IsoTileMap();

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

