#pragma once
//�ﰢ��
class Rect : public Object
{
private:
    //�׳� ����� d3d����
    ID3D11Buffer*		VertexBuffer;
    UINT				VertexCount;//��������
    VertexPC*           Vertex;
    bool                isFill;
    //Vector2   Vertex[4];
public:
    Rect(Vector2 pivot = Vector2(0.0f, 0.0f)
        , bool isfill = true);
    ~Rect();
    //�߽��� ��� �ΰ� �����ǰ�?

    void Init()override;
    void WorldUpdate()override;
    void Render()override;
};

