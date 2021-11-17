#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh()
{
    vertexType = VertexType::V_PC;
    VertexPC* Vertex;
    switch (vertexType)
    {
    case VertexType::V_P:
        byteWidth = sizeof(VertexP);
        break;
    case VertexType::V_PC:
        byteWidth = sizeof(VertexPC);
        break;
    }
    //3°³ÀÇ ¸é 4*3
    Vertex = new VertexPC[12];
    vertexCount = 12;
    //3*2*3 ÀÇ ÀÎµ¦½º
    indices = new UINT[18];
    indexCount = 18;

    //0,1,2,3 (»¡°£»ö)
    Vertex[0].position = Vector3(-1, -1, -1);
    Vertex[0].color = Color(1, 0, 0);
    Vertex[1].position = Vector3(-1, 1, -1);
    Vertex[1].color = Color(1, 0, 0);
    Vertex[2].position = Vector3(1, 1, -1);
    Vertex[2].color = Color(1, 0, 0);
    Vertex[3].position = Vector3(1, -1, -1);
    Vertex[3].color = Color(1, 0, 0);

    
    //»¡°£»ö¸é
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    //4,5,6,7 (³ì»ö)
    Vertex[4].position = Vector3(1, -1, -1);
    Vertex[4].color = Color(0, 1, 0);
    Vertex[5].position = Vector3(1, 1, -1);
    Vertex[5].color = Color(0, 1, 0);
    Vertex[6].position = Vector3(1, 1, 1);
    Vertex[6].color = Color(0, 1, 0);
    Vertex[7].position = Vector3(1, -1, 1);
    Vertex[7].color = Color(0, 1, 0);

    indices[6] = 4;
    indices[7] = 5;
    indices[8] = 6;

    indices[9] = 6;
    indices[10] = 7;
    indices[11] = 4;

    //8,9,10,11 (ÆÄ¶õ»ö)
    Vertex[8].position = Vector3(-1, 1, -1);
    Vertex[8].color = Color(0, 0, 1);
    Vertex[9].position = Vector3(-1, 1, 1);
    Vertex[9].color = Color(0, 0, 1);
    Vertex[10].position = Vector3(1, 1, 1);
    Vertex[10].color = Color(0, 0, 1);
    Vertex[11].position = Vector3(1, 1, -1);
    Vertex[11].color = Color(0, 0, 1);

    indices[0 + 12] = 8;
    indices[1 + 12] = 9;
    indices[2 + 12] = 10;

    indices[3 + 12] = 10;
    indices[4 + 12] = 11;
    indices[5 + 12] = 8;


    vertices = (void*)Vertex;
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = byteWidth * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //Create Index Buffer
    {
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(UINT) * indexCount;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = indices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
        assert(SUCCEEDED(hr));
    }
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
}

Mesh::~Mesh()
{
    switch (vertexType)
    {
    case VertexType::V_P:
        delete[] (VertexP*)vertices;
        break;
    case VertexType::V_PC:
        delete[] (VertexPC*)vertices;
        break;
    }

    SafeRelease(vertexBuffer);
    SafeRelease(indexBuffer);
}

void Mesh::Set()
{
    UINT offset = 0;
    D3D->GetDC()->IASetVertexBuffers(0,
        1,
        &vertexBuffer,
        &byteWidth,
        &offset);
    D3D->GetDC()->IASetPrimitiveTopology
    (primitiveTopology);
    D3D->GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}
