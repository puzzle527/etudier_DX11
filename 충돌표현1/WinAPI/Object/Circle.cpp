#include "stdafx.h"
#include "Circle.h"

Circle::Circle(UINT slice, Vector2 pivot)
{
    this->Slice = slice;

    float Seta = 2.0f * PI / (float)Slice;

    //36조각일때 삼각형 몇개? 36
    VertexCount = Slice * 3;

    Vertex = new VertexPC[VertexCount];
    //RenderVertex = new Vector2[Slice];

    for(UINT i = 0; i < Slice; i++)
    {
        Vertex[i * 3].Position.x = 0.0f - pivot.x;
        Vertex[i * 3].Position.y = 0.0f - pivot.y;
        Vertex[i * 3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i * 3 + 1].Position.x = cosf(Seta*(i + 1))*0.5f - pivot.x;
        Vertex[i * 3 + 1].Position.y = sinf(Seta*(i + 1))*0.5f - pivot.y;
        float y = Vertex[i * 3 + 1].Position.y;
        Vertex[i * 3 + 1].color = 
            Color(0.5f + y, 0, 0.5f - y, 1.0f);
        Vertex[i * 3 + 2].Position.x = cosf(Seta*(i))*0.5f - pivot.x;
        Vertex[i * 3 + 2].Position.y = sinf(Seta*(i))*0.5f - pivot.y;
        y = Vertex[i * 3 + 2].Position.y;
        Vertex[i * 3 + 2].color =
            Color(0.5f + y, 0, 0.5f - y, 1.0f);
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

    //정점 서술
    D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
    {
        { "POSITION",//시멘틱에서 정의한 자료형
        0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
        DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
        0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
        0,//이 요소가 메모리덩어리 시작지점부터 얼마나 떨어진 위치에 있는가를 알려준다.처음시작0
        D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
        0 },//넘어가기
    { "COLOR",//시멘틱에서 정의한 자료형
    0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
    DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
    0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
    12,//포지션 R32G32B32 4 ,4,4 ->12
    D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
    0 }
    };

    shader = new Shader(_T("./Shader/1.Basic.hlsl"));
    UINT ElementCount = ARRAYSIZE(LayoutDesc);
    shader->CreateInputLayout(LayoutDesc, ElementCount);
    Pivot = pivot;
}

Circle::~Circle()
{
    SAFE_DELETE_ARRAY(Vertex);
    SAFE_RELEASE(VertexBuffer);
}

void Circle::Init()
{
    Object::Init();
}

void Circle::WorldUpdate()
{
    Object::WorldUpdate();
}

void Circle::Render()
{
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
    g_DeviceContext->Draw(VertexCount, 0);
}
