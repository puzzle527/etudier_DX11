#pragma once
//�ﰢ��
class Rect : public Object
{
private:
    //�׳� ����� d3d����
    ID3D11Buffer*		VertexBuffer;   //����
    UINT				VertexCount;    //��������
    VertexPC*           Vertex;         //�����迭
    /*Vector2             Verterx[4];*/
public:
    Rect(Vector2 pivot = Vector2(0.0f, 0.0f));
    ~Rect();
    //�߽��� ��� �ΰ� �����ǰ�?
    
    void Init()override;
    void WorldUpdate()override;
    void Render()override;
};

