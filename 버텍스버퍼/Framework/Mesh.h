#pragma once
class Mesh 
{
    //����(������),������ �մ� Ÿ��(��,��,��),

    //������ ���¸����
    //���������������� ��ǥ(�����ǥ) x,y,z,w
    //��
    //�ؽ�ó ��ǥ (uv)
    ID3D11Buffer*           vertexBuffer;
    //VertexP*                 vectex;
    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;
public:
    UINT                    vertexCount;
    Mesh();
    ~Mesh();

    void Set(); // binding
};

