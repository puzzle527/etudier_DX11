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

    
    Vertex = new VertexPC[1];
    vertexCount = 1;
    indices = new UINT[1];
    indexCount = 1;

    //0,1,2,3 (빨간색)
    Vertex[0].position = Vector3(0, 0, 0);
    Vertex[0].color = Color(1, 0, 0);


    //빨간색면
    indices[0] = 0;





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
    this->file = file;
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
