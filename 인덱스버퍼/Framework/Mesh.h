#pragma once
class Mesh 
{
    //����(������),������ �մ� Ÿ��(��,��,��),

    //������ ���¸����
    //���������������� ��ǥ(�����ǥ) x,y,z,w
    //��
    //�ؽ�ó ��ǥ (uv)
    ID3D11Buffer*           vertexBuffer;
    ID3D11Buffer*           indexBuffer;
    UINT                    byteWidth;
public:
    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;
    VertexType              vertexType;

    UINT                    vertexCount;
    void*                   vertices;
    UINT                    indexCount;
    UINT*                   indices;

    Mesh();
    ~Mesh();

    void Set(); // binding
};

