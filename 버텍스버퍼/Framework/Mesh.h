#pragma once
class Mesh 
{
    //정점(꼭지점),정점을 잇는 타입(선,점,면),

    //점들이 갖는멤버값
    //기준점에서부터의 좌표(상대좌표) x,y,z,w
    //색
    //텍스처 좌표 (uv)
    ID3D11Buffer*           vertexBuffer;
    //VertexP*                 vectex;
    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;
public:
    UINT                    vertexCount;
    Mesh();
    ~Mesh();

    void Set(); // binding
};

