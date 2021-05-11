#pragma once
//��
class Line : public Object
{
private:
    //�׳� ����� d3d����
    ID3D11Buffer*		VertexBuffer;
    UINT				VertexCount;//��������
    VertexPC*           Vertex;


public:
    Line(Vector2 pivot = Vector2(-0.5f, 0));
    ~Line();
    void Init() override;
    void WorldUpdate() override;
    void Render() override;
};


