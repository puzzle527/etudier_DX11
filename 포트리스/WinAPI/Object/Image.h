#pragma once
class Image : public Object
{
private:
    //�׳� ����� d3d����
    ID3D11Buffer* VertexBuffer;
    UINT				VertexCount;//��������
    VertexPT*   Vertex;
    //           ���̴��ڿ���
    //�ڿ������ ���������ο� �ڿ��� �����Ҷ�
    ID3D11ShaderResourceView* srv;
public:
    Image(_tstring file, Vector2 pivot = Vector2(0.0f, 0.0f));
    ~Image();
    //�߽��� ��� �ΰ� �����ǰ�?

    void Init()override;
    void WorldUpdate()override;
    void Render()override;
};

