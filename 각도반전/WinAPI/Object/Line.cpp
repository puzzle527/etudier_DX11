#include "stdafx.h"
#include "Line.h"

Line::Line(Vector2 pivot)
{
    Vertex = new VertexPC[2];
    VertexCount = 2;

    Vertex[0].Position.x = -0.5f - pivot.x;
    Vertex[0].Position.y = 0.0f - pivot.y;
    Vertex[0].color = Color(0, 0, 0, 1.0f);

    Vertex[1].Position.x = 0.5f - pivot.x;
    Vertex[1].Position.y = 0.0f - pivot.y;
    Vertex[1].color = Color(0, 0, 0, 1.0f);

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

Line::~Line()
{
    SAFE_DELETE_ARRAY(Vertex);
    SAFE_RELEASE(VertexBuffer);
}

void Line::Init()
{
    Object::Init();
}

void Line::WorldUpdate()
{
    if (!isActive)return;
    Object::WorldUpdate();
}

void Line::Render()
{
    if (!isActive)return;
    //상수버퍼 업데이트 W값을 WBuffer에 전달
    g_DeviceContext->UpdateSubresource(WBuffer, 0, NULL, &W, 0, 0);
    //                            연결될레지스터 번호 0
    g_DeviceContext->VSSetConstantBuffers(0, 1, &WBuffer);


    shader->SetShader();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;
    //정점의 도형서술
    g_DeviceContext->IASetPrimitiveTopology
        //(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        (D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    g_DeviceContext->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
        1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
        &VertexBuffer,
        &stride,//정점버퍼의 한 원소의 바이트단위 크기
        &offset);

    //그려라 라는 명령
    g_DeviceContext->Draw(VertexCount, 0);

}