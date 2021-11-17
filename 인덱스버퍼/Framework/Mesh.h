#pragma once
class Mesh 
{
    //정점(꼭지점),정점을 잇는 타입(선,점,면),

    //점들이 갖는멤버값
    //기준점에서부터의 좌표(상대좌표) x,y,z,w
    //색
    //텍스처 좌표 (uv)
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

