#pragma once
//원 도형 만들기
class Star :public Object
{
private:
    ID3D11Buffer*		VertexBuffer;
    UINT				VertexCount;//정점갯수
    VertexPC*           Vertex;
public:

    Star(Vector2 pivot = Vector2(0.0f, 0.0f));
    ~Star();
    void Init() override;
    void WorldUpdate() override;
    void Render() override;
};

