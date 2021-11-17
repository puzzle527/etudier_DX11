#include "stdafx.h"
#include "Image.h"


Image::Image(_tstring file, Vector2 pivot)
{
    srv = RESOURCEMANAGER->LoadTexture(file);

    //기본 샘플러 값
    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // 소수점 버리기
    //SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; //선형으로 보간

    //0~1 사이값을 벗어나는 좌표를 사용할때 바꾸는 옵션
    //D3D11_TEXTURE_ADDRESS_CLAMP 마지막 픽셀값으로 색을 채운다.
    //D3D11_TEXTURE_ADDRESS_WRAP 0 1 넘어가는걸 다시 0~1값으로 가둔다.
    //D3D11_TEXTURE_ADDRESS_MIRROR 0 1 넘어가는걸 뒤집어서 0~1값으로 가둔다.
    SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    SamplerDesc.MipLODBias = 0.0f;
    SamplerDesc.MaxAnisotropy = 1;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    SamplerDesc.MinLOD = -FLT_MAX;
    SamplerDesc.MaxLOD = FLT_MAX;

    //하나 이상의 샘플러 만들어 두기
    g_Device->CreateSamplerState(&SamplerDesc, &Sampler);






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

    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Vector4);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &UVBuffer);
        assert(SUCCEEDED(hr));
    }
    shader = RESOURCEMANAGER->ShaderArray[1];
    Pivot = pivot;
}

Image::~Image()
{
    SAFE_DELETE_ARRAY(Vertex);
    SAFE_RELEASE(VertexBuffer);
    SAFE_RELEASE(UVBuffer);
    SAFE_RELEASE(Sampler);
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
    //연결될레지스터 번호 0
    g_DeviceContext->PSSetSamplers(0,
        1, //리소스갯수
        &Sampler);//샘플러

    //애니메이션 재생 함수
    PlayAnim();

    g_DeviceContext->UpdateSubresource(UVBuffer, 0, NULL, &UV, 0, 0);
    //                            연결될레지스터 번호4
    g_DeviceContext->VSSetConstantBuffers(4, 1, &UVBuffer);




    g_DeviceContext->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
        1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
        &VertexBuffer,
        &stride,//정점버퍼의 한 원소의 바이트단위 크기
        &offset);
    //정점의 도형정의
    g_DeviceContext->IASetPrimitiveTopology
    (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //블렌드 켜기
    g_DeviceContext->OMSetBlendState(g_BlendState[1], NULL, 0xFF);
    g_DeviceContext->Draw(VertexCount, 0);
    //블렌드 끄기
    g_DeviceContext->OMSetBlendState(g_BlendState[0], NULL, 0xFF);
}

void Image::ChangeFilter(Sampling sam)
{
    if (sam == _POINT)
    {
        SamplerDesc.Filter =
            D3D11_FILTER_MIN_MAG_MIP_POINT;
        //기존 샘플러 삭제
        SAFE_RELEASE(Sampler);
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _LINEAR)
    {
        SamplerDesc.Filter =
            D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        SAFE_RELEASE(Sampler);
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
}

void Image::ChangeAddress(Sampling sam)
{

    if (sam == _CLAMP)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

        SAFE_RELEASE(Sampler);
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _WRAP)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

        SAFE_RELEASE(Sampler);
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _MIRROR)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
        SAFE_RELEASE(Sampler);
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
}

void Image::PlayAnim()
{
    //분할갯수가 1이상일때
    if (MaxFrame.x != 1 || MaxFrame.y != 1)
    {
        //정지가 아닌경우에만
        if (AnimState != _STOP)
        {
            //시간 경과량
            AnimTime += DeltaTime;
            //경과량이 재생간격보다 커질때
            if (AnimTime > AnimInterval)
            {
                AnimTime -= AnimInterval;

                //가로축 재생인가?
                if (AnimXAxis)
                {
                    //정방향 재생
                    if (AnimState == _LOOP)
                    {
                        Frame.x++;
                        if (Frame.x == MaxFrame.x)Frame.x = 0;
                    }
                    //역방향 재생
                    else if (AnimState == _MIRRORLOOP)
                    {
                        Frame.x--;
                        if (Frame.x == -1)Frame.x = MaxFrame.x - 1;
                    }
                    //정방향 재생
                    else if (AnimState == _ONCE)
                    {
                        Frame.x++;
                        if (Frame.x == MaxFrame.x)
                        {
                            AnimState = _STOP;
                            Frame.x = MaxFrame.x - 1;
                        }
                    }
                    //역방향 재생
                    else if (AnimState == _MIRRORONCE)
                    {
                        Frame.x--;
                        if (Frame.x == -1)
                        {
                            AnimState = _STOP;
                            Frame.x = 0;
                        }
                    }
                }
                //세로축 재생인가?
                else
                {
                    //정방향 재생
                    if (AnimState == _LOOP)
                    {
                        Frame.y++;
                        if (Frame.y == MaxFrame.y)Frame.y = 0;
                    }
                    //역방향 재생
                    else if (AnimState == _MIRRORLOOP)
                    {
                        Frame.y--;
                        if (Frame.y == -1)Frame.y = MaxFrame.y - 1;
                    }
                    //정방향 재생
                    else if (AnimState == _ONCE)
                    {
                        Frame.y++;
                        if (Frame.y == MaxFrame.y)
                        {
                            AnimState = _STOP;
                            Frame.y = MaxFrame.y - 1;
                        }
                    }
                    //역방향 재생
                    else if (AnimState == _MIRRORONCE)
                    {
                        Frame.y--;
                        if (Frame.y == -1)
                        {
                            AnimState = _STOP;
                            Frame.y = 0;
                        }
                    }
                }
            }

        }
        UV.x = Frame.x / (float)MaxFrame.x;
        UV.z = (Frame.x + 1.0f) /
            (float)MaxFrame.x;
        UV.y = Frame.y / (float)MaxFrame.y;
        UV.w = (Frame.y + 1.0f) /
            (float)MaxFrame.y;
    }
}



void Image::ChangeAnim(Animation anim, float interval, bool XAxis)
{
    AnimTime = 0.0f;    //재생시간 0으로 초기화
    AnimState = anim;   //상태값 대입
    AnimXAxis = XAxis;  //재생축 대입
    AnimInterval = interval; //재생간격 대입
    //한번 재생이라면(시트 맨 앞이미지로 이동)
    if (AnimState == _ONCE)
    {
        if (XAxis)
            Frame.x = 0;
        else
            Frame.y = 0;
    }
    if (AnimState == _MIRRORONCE)
    {
        if (XAxis)
            Frame.x = MaxFrame.x - 1;
        else
            Frame.y = MaxFrame.y - 1;
    }
}
