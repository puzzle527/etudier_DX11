#include "stdafx.h"
#include "Image.h"

Image::Image(_tstring file, Vector2 pivot)
{
    _tstring textureFile = _T("./Images/") + file;

    HRESULT hr;

    //jpg,png,gif,bmp 정도는 불러올수있음
    D3DX11CreateShaderResourceViewFromFile
    (
        g_Device,//디바이스
        textureFile.c_str(),//파일이름
        NULL, //추가적인 이미지 정보 NULL값은 원본크기
        NULL,//널값
        &srv,//쉐이더자원뷰
        &hr
    );
    assert(SUCCEEDED(hr) && "텍스쳐로드 실패");



    Vertex = new VertexPT[6];
    VertexCount = 6;
    //시계방향으로 정점찍기
    Vertex[0].Position.x = -pivot.x - 0.5f;
    Vertex[0].Position.y = -pivot.y - 0.5f;
    Vertex[0].Uv.x = 0.0f;
    Vertex[0].Uv.y = 1.0f;



    Vertex[1].Position.x = -pivot.x - 0.5f;
    Vertex[1].Position.y = -pivot.y + 0.5f;
    Vertex[1].Uv.x = 0.0f;
    Vertex[1].Uv.y = 0.0f;

    Vertex[2].Position.x = -pivot.x + 0.5f;
    Vertex[2].Position.y = -pivot.y - 0.5f;
    //검은색
    Vertex[2].Uv.x = 1.0f;
    Vertex[2].Uv.y = 1.0f;

    Vertex[3].Position.x = -pivot.x - 0.5f;
    Vertex[3].Position.y = -pivot.y + 0.5f;
    Vertex[3].Uv.x = 0.0f;
    Vertex[3].Uv.y = 0.0f;

    Vertex[4].Position.x = -pivot.x + 0.5f;
    Vertex[4].Position.y = -pivot.y + 0.5f;
    Vertex[4].Uv.x = 1.0f;
    Vertex[4].Uv.y = 0.0f;

    Vertex[5].Position.x = +0.5f - pivot.x;
    Vertex[5].Position.y = -0.5f - pivot.y;
    Vertex[5].Uv.x = 1.0f;
    Vertex[5].Uv.y = 1.0f;

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPT) * VertexCount; //버퍼 크기 (바이트)입니다.
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
        { "UV",//시멘틱에서 정의한 자료형
        0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
        DXGI_FORMAT_R32G32_FLOAT,//3개의 32비트 float설정
        0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
        12,//포지션 R32G32B32 4 ,4,4 ->12
        D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
        0 }
    };

    shader = new Shader(_T("./Shader/2.Image.hlsl"));
    UINT ElementCount = ARRAYSIZE(LayoutDesc);
    shader->CreateInputLayout(LayoutDesc, ElementCount);

    Pivot = pivot;
}

Image::~Image()
{
    SAFE_DELETE_ARRAY(Vertex);
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(srv);
}

void Image::Init()
{
    Object::Init();
}

void Image::WorldUpdate()
{
    if (!isActive)return;
    //재정의된 스타로 호출될때
   //부모함수도 호출
    Object::WorldUpdate();
}

void Image::Render()
{
    if (!isActive)return;
    Object::Render();

    shader->SetShader();

    UINT stride = sizeof(VertexPT);
    UINT offset = 0;

    //픽셀쉐이더에 쉐이더자원값 세팅
    g_DeviceContext->PSSetShaderResources(0,// 연결될레지스터 번호 0
        1,//리소스갯수
        &srv);


    g_DeviceContext->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
        1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
        &VertexBuffer,
        &stride,//정점버퍼의 한 원소의 바이트단위 크기
        &offset);
    //정점의 도형정의
    g_DeviceContext->IASetPrimitiveTopology
    (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g_DeviceContext->Draw(VertexCount, 0);
}
