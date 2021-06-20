#pragma once
//삼각형
class Rect : public Object
{
private:
    //그냥 평범한 d3d버퍼
    ID3D11Buffer*		VertexBuffer;
    UINT				VertexCount;//정점갯수
    VertexPC*           Vertex;
    bool                isFill;
    //Vector2   Vertex[4];
public:
    Rect(Vector2 pivot = Vector2(0.0f, 0.0f)
        , bool isfill = true);
    ~Rect();
    //중심을 어디에 두고 찍을건가?

    void Init()override;
    void WorldUpdate()override;
    void Render()override;
};

