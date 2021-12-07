#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh()
    :vertices(nullptr),indices(nullptr)
    , vertexBuffer(nullptr),indexBuffer(nullptr)
{
    //file = "Cube.mesh";

    vertexType = VertexType::V_PC;
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
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

    
    Vertex = new VertexPC[24];
    vertexCount = 24;
    indices = new UINT[36];
    indexCount = 36;


    //0,1,2,3 (빨간색)
    Vertex[0].position = Vector3(-1, -1, -1);
    Vertex[0].color = Color(1.5f, 1.5f, 1.5f);
    Vertex[1].position = Vector3(-1, 1, -1);
    Vertex[1].color = Color(0.5f, 0.5f, 1.5f);
    Vertex[2].position = Vector3(1, 1, -1);
    Vertex[2].color = Color(0.5f, 1.5f, 0.5f);
    Vertex[3].position = Vector3(1, -1, -1);
    Vertex[3].color = Color(0.5f, 0.5f, 0.5f);

    
    //빨간색면
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    //4,5,6,7 (녹색)
    Vertex[4].position = Vector3(1, -1, -1);
    Vertex[4].color = Color(1.5f, 0.5f, 0.5f);
    Vertex[5].position = Vector3(1, 1, -1);
    Vertex[5].color = Color(0.5f, 0.5f, 1.5f);
    Vertex[6].position = Vector3(1, 1, 1);
    Vertex[6].color = Color(0.5f, 0.5f, 1.5f);
    Vertex[7].position = Vector3(1, -1, 1);
    Vertex[7].color = Color(0.5f, 1.5f, 0.5f);

    indices[6] = 4;
    indices[7] = 5;
    indices[8] = 6;

    indices[9] = 6;
    indices[10] = 7;
    indices[11] = 4;

    //8,9,10,11 (파란색)
    Vertex[8].position = Vector3(-1, 1, -1);
    Vertex[8].color = Color(0.5f, 0.5f, 1.5f);
    Vertex[9].position = Vector3(-1, 1, 1);
    Vertex[9].color = Color(0.5f, 0.5f, 1.5f);
    Vertex[10].position = Vector3(1, 1, 1);
    Vertex[10].color = Color(1.5f, 0.5f, 0.5f);
    Vertex[11].position = Vector3(1, 1, -1);
    Vertex[11].color = Color(0.5f, 0.0f, 0.5f);

    indices[0 + 12] = 8;
    indices[1 + 12] = 9;
    indices[2 + 12] = 10;

    indices[3 + 12] = 10;
    indices[4 + 12] = 11;
    indices[5 + 12] = 8;

    //12,13,14,15 (노란색)
    Vertex[12].position = Vector3(-1, -1, -1);
    Vertex[12].color = Color(0.5f, 0.5f, 0.5f);
    Vertex[13].position = Vector3(-1, -1, 1);
    Vertex[13].color = Color(0.5f, 1.5f, 0.5f);
    Vertex[14].position = Vector3(1, -1, 1);
    Vertex[14].color = Color(0.5f, 0.5f, 0.5f);
    Vertex[15].position = Vector3(1, -1, -1);
    Vertex[15].color = Color(0.5f, 1.5f, 0.5f);


    //노란색
    indices[18] = 13;
    indices[19] = 12;
    indices[20] = 14;

    indices[21] = 15;
    indices[22] = 14;
    indices[23] = 12;

    //16,17,18,19 (분홍색)
    Vertex[16].position = Vector3(-1, -1, 1);
    Vertex[16].color = Color(0.5f, 0.5f, 0.5f);
    Vertex[17].position = Vector3(-1, 1, 1);
    Vertex[17].color = Color(1.5f, 0.5f, 0.5f);
    Vertex[18].position = Vector3(1, 1, 1);
    Vertex[18].color = Color(0.5f, 0.8f, 0.2f);
    Vertex[19].position = Vector3(1, -1, 1);
    Vertex[19].color = Color(0.5f, 0.5f, 0.5f);


    //분홍색면
    indices[24] = 17;
    indices[25] = 16;
    indices[26] = 18;

    indices[27] = 19;
    indices[28] = 18;
    indices[29] = 16;

    //20,21,22,23 (하늘색)
    Vertex[20].position = Vector3(-1, -1, -1);
    Vertex[20].color = Color(1.5f, 0.5f, 0.5f);
    Vertex[21].position = Vector3(-1, 1, -1);
    Vertex[21].color = Color(0.5f, 0.5f, 0.5f);
    Vertex[22].position = Vector3(-1, 1, 1);
    Vertex[22].color = Color(0.5f, 0.5f, 0.5f);
    Vertex[23].position = Vector3(-1, -1, 1);
    Vertex[23].color = Color(0.5f, 0.1f, 0.5f);


    //하늘색면
    indices[30] = 21;
    indices[31] = 20;
    indices[32] = 22;

    indices[33] = 23;
    indices[34] = 22;
    indices[35] = 20;






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
