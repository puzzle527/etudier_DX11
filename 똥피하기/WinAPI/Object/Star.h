#pragma once
class Star : public Object
{
private:
    ID3D11Buffer*		VertexBuffer;
    UINT				VertexCount;//Á¤Á¡°¹¼ö
    VertexPC*           Vertex;
public:

    Star(Vector2 pivot = Vector2(0.0f, 0.0f));
    ~Star();
    void Init() override;
    void WorldUpdate() override;
    void Render() override;
};

