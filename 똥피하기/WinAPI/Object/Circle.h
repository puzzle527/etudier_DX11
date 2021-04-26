#pragma once
//�� ���� �����
class Circle :public Object
{
private:
    UINT                Slice;

    ID3D11Buffer*		VertexBuffer;
    UINT				VertexCount;//��������
    VertexPC*           Vertex;
public:
   
    Circle(UINT Slice = 36,
        Vector2 pivot = Vector2(0.0f, 0.0f));
    ~Circle();
    void Init() override;
    void WorldUpdate() override;
    void Render() override;
};

