#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh()
{
    VertexP* Vertex;
    /*VertexP  Vertex2[4];
    Vertex2; Vertex;
    Vertex2[2]; Vertex[1];
    Vertex = Vertex2;
    Vertex2 = Vertex;*/

    Vertex = new VertexP[4];
    vertexCount = 4;


    //VertexCount = 4;
    
    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = -0.5f;

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = 0.5f;

    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = -0.5f;

    Vertex[3].position.x = 0.5f;
    Vertex[3].position.y = 0.5f;


    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(VertexP) * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = Vertex;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    delete[] Vertex;

   
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
}

Mesh::~Mesh()
{
    SafeRelease(vertexBuffer);
}

void Mesh::Set()
{
    UINT stride = sizeof(VertexP);
    UINT offset = 0;
    D3D->GetDC()->IASetVertexBuffers(0,
        1,
        &vertexBuffer,
        &stride,
        &offset);
    D3D->GetDC()->IASetPrimitiveTopology
    (primitiveTopology);
}
