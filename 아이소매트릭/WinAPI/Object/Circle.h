#pragma once
//�� ���� �����
class Circle :public Object
{
private:
    UINT                Slice;

    ID3D11Buffer*		VertexBuffer;
    UINT				VertexCount;//��������
    VertexPC*           Vertex;
    bool                isFill;
public:

    Circle(UINT Slice = 36,
        Vector2 pivot = Vector2(0.0f, 0.0f)
        , bool isfill = true);
    ~Circle();
    void Init() override;
    void WorldUpdate() override;
    void Render() override;
};

