#pragma once
//선
class Line : public Object
{
private:
    //그냥 평범한 d3d버퍼
    ID3D11Buffer*		VertexBuffer;
    UINT				VertexCount;//정점갯수
    VertexPC*           Vertex;


public:
    Line(Vector2 pivot = Vector2(-0.5f, 0));
    ~Line();
    void Init() override;
    void WorldUpdate() override;
    void Render() override;
};


