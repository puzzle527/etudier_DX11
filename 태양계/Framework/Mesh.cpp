#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh()
    :vertices(nullptr),indices(nullptr)
    , vertexBuffer(nullptr),indexBuffer(nullptr)
{
    //file = "Cube.mesh";

    vertexType = VertexType::V_PC;
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
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
    ////////////////////////////////////////////////////

    int ColCount = 500; //짝수는 안됨
    int Width = 50; //좌표단위
    int harfCount = ColCount / 2;
    int harfWidth = harfCount * Width;

    Vertex = new VertexPC[ColCount*4];
    vertexCount = ColCount * 4;



    indices = new UINT[ColCount * 4];
    indexCount = ColCount * 4;

    int Count = 0;
    for (int i = 0; i < ColCount*4; i+=4)
    {
        Vertex[i].position = 
            Vector3(-harfWidth + Width * Count, 0, -harfWidth);
        Vertex[i].color = Color(1, 1, 1);

        Vertex[i+1].position = 
            Vector3(-harfWidth + Width * Count, 0, harfWidth);
        Vertex[i+1].color = Color(1, 1, 1);

        Vertex[i + 2].position =
            Vector3(-harfWidth , 0, -harfWidth + Width * Count);
        Vertex[i + 2].color = Color(1, 1, 1);

        Vertex[i + 3].position =
            Vector3(harfWidth , 0, -harfWidth + Width * Count);
        Vertex[i + 3].color = Color(1, 1, 1);
        Count++;
    }

    for (UINT i = 0; i < indexCount; i++)
    {
        indices[i] = i;
    }






    ///////////////////////////////////////////////////
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

void Mesh::LoadFile(string file)
{
    
    //읽기전
    switch (vertexType)
    {
    case VertexType::V_P:
        if (vertices)delete[](VertexP*)vertices;
        break;
    case VertexType::V_PC:
        if (vertices)delete[](VertexPC*)vertices;
        break;
    }
   
    BinaryReader in;
    wstring path = L"../Contents/Mesh/" + String::ToWString(file) + L".mesh";
    in.Open(path);

    vertexType = (VertexType)in.UInt();
    primitiveTopology = (D3D_PRIMITIVE_TOPOLOGY)in.UInt();
    byteWidth = in.UInt();
    vertexCount = in.UInt();
    indexCount = in.UInt();

    SafeDeleteArray(indices);
    indices = new UINT[indexCount];


    //읽고난후
    switch (vertexType)
    {
    case VertexType::V_P:
    {
        vertices = new VertexP[vertexCount];
        VertexP* vertex = (VertexP*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
        }
        break;
    }

    case VertexType::V_PC:
    {
        vertices = new VertexPC[vertexCount];
        VertexPC* vertex = (VertexPC*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].color = in.color3f();
        }
        break;
    }

    }
    for (UINT i = 0; i < indexCount; i++)
    {
        indices[i] = in.UInt();
    }
    in.Close();

    SafeRelease(vertexBuffer);
    SafeRelease(indexBuffer);
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

}

void Mesh::SaveFile(string file)
{
    BinaryWriter out;
    wstring path = L"../Contents/Mesh/" + String::ToWString(file) + L".mesh";
    out.Open(path);

    out.UInt((UINT)vertexType);
    out.UInt((UINT)primitiveTopology);
    out.UInt(byteWidth);
    out.UInt(vertexCount);
    out.UInt(indexCount);

    switch (vertexType)
    {
    case VertexType::V_P :
    {
        VertexP* vertex = (VertexP*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
        }
        break;
    }
        
    case VertexType::V_PC:
    {
        VertexPC* vertex = (VertexPC*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.color3f(vertex[i].color);
        }
        break;
    }
        
    }
    for (UINT i = 0; i < indexCount; i++)
    {
        out.UInt(indices[i]);
    }
    out.Close();
}
