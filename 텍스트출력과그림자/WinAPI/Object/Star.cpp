#include "stdafx.h"
#include "Star.h"

Star::Star( Vector2 pivot)
{

    float Seta = 4.0f * PI / 5.0f;

    //36조각일때 삼각형 몇개? 36
    VertexCount = 15;

    Vertex = new VertexPC[VertexCount];
    //RenderVertex = new Vector2[Slice];

    Color col1 = Color(RndFloat(), RndFloat(), RndFloat(),1.0f);
    Color col2 = Color(RndFloat(), RndFloat(), RndFloat(), 1.0f);

    for(UINT i = 0; i < 5; i++)
    {
        Vertex[i * 3].Position.x = 0.0f - pivot.x;
        Vertex[i * 3].Position.y = 0.0f - pivot.y;
        Vertex[i * 3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i * 3 + 1].Position.x = cosf(Seta*(i + 1))*0.5f - pivot.x;
        Vertex[i * 3 + 1].Position.y = sinf(Seta*(i + 1))*0.5f - pivot.y;
        
        Vertex[i * 3 + 1].color =
            Color(0.0f, 0.0f, 0.0f, 1.0f);
        Vertex[i * 3 + 2].Position.x = cosf(Seta*(i))*0.5f - pivot.x;
        Vertex[i * 3 + 2].Position.y = sinf(Seta*(i))*0.5f - pivot.y;
       
        Vertex[i * 3 + 2].color =
            Color(0.0f, 0.0f, 0.0f, 1.0f);
        //Vertex[i].x = cosf(Seta*i)*0.5f;
        //Vertex[i].y = sinf(Seta*i)*0.5f;
    }
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * VertexCount; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
        HRESULT hr = g_Device->CreateBuffer(&desc, &data, &VertexBuffer);
        assert(SUCCEEDED(hr));
    }
    shader = RESOURCEMANAGER->ShaderArray[0];
    Pivot = pivot;
}

Star::~Star()
{
    SAFE_DELETE_ARRAY(Vertex);
    SAFE_RELEASE(VertexBuffer);
}

void Star::Init()
{
    Object::Init();
}

void Star::WorldUpdate()
{
    if (!isActive)return;
    Object::WorldUpdate();
}

void Star::Render()
{
    if (!isActive)return;
    Object::Render();
    shader->SetShader();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;
    g_DeviceContext->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
        1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
        &VertexBuffer,
        &stride,//정점버퍼의 한 원소의 바이트단위 크기
        &offset);

    //정점의 도형서술
    g_DeviceContext->IASetPrimitiveTopology
    (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);


    //DrawCall
   //블렌드 켜기
    g_DeviceContext->OMSetBlendState(g_BlendState[1], NULL, 0xFF);
    g_DeviceContext->Draw(VertexCount, 0);
    //블렌드 끄기
    g_DeviceContext->OMSetBlendState(g_BlendState[0], NULL, 0xFF);
}
