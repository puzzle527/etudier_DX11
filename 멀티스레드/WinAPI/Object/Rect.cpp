#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Vector2 pivot, bool isfill)
{
    isFill = isfill;
    //속이 차있는 네모
    if (isFill)
    {
        Vertex = new VertexPC[6];
        VertexCount = 6;
        //시계방향으로 정점찍기
        Vertex[0].Position.x = -pivot.x - 0.5f;
        Vertex[0].Position.y = -pivot.y - 0.5f;
        //흰색
        Vertex[0].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[1].Position.x = -pivot.x - 0.5f;
        Vertex[1].Position.y = -pivot.y + 0.5f;
        //흰색
        Vertex[1].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[2].Position.x = -pivot.x + 0.5f;
        Vertex[2].Position.y = -pivot.y - 0.5f;
        //검은색
        Vertex[2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

        Vertex[3].Position.x = -pivot.x - 0.5f;
        Vertex[3].Position.y = -pivot.y + 0.5f;
        //흰색
        Vertex[3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[4].Position.x = -pivot.x + 0.5f;
        Vertex[4].Position.y = -pivot.y + 0.5f;
        //파란색
        Vertex[4].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

        Vertex[5].Position.x = +0.5f - pivot.x;
        Vertex[5].Position.y = -0.5f - pivot.y;
        //파란색
        Vertex[5].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    }
    else
    {
        Vertex = new VertexPC[5];
        VertexCount = 5;
        Vertex[0].Position.x = -pivot.x - 0.5f;
        Vertex[0].Position.y = -pivot.y - 0.5f;
        Vertex[0].color =  Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[1].Position.x = -pivot.x - 0.5f;
        Vertex[1].Position.y = -pivot.y + 0.5f;
        Vertex[1].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[2].Position.x = -pivot.x + 0.5f;
        Vertex[2].Position.y = -pivot.y + 0.5f;
        Vertex[2].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[3].Position.x = -pivot.x + 0.5f;
        Vertex[3].Position.y = -pivot.y - 0.5f;
        Vertex[3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[4].Position.x = -pivot.x - 0.5f;
        Vertex[4].Position.y = -pivot.y - 0.5f;
        Vertex[4].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
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

Rect::~Rect()
{
    SAFE_DELETE_ARRAY(Vertex);
    SAFE_RELEASE(VertexBuffer);
}

void Rect::Init()
{
    Object::Init();

}

void Rect::WorldUpdate()
{
    if (!isActive)return;
    //재정의된 스타로 호출될때
   //부모함수도 호출
    Object::WorldUpdate();

}

void Rect::Render()
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
    //정점의 도형정의
    if (isFill)
    {
        g_DeviceContext->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
    else
    {
        g_DeviceContext->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    }
    //블렌드 켜기
    g_DeviceContext->OMSetBlendState(g_BlendState[1], NULL, 0xFF);
    g_DeviceContext->Draw(VertexCount, 0);
    //블렌드 끄기
    g_DeviceContext->OMSetBlendState(g_BlendState[0], NULL, 0xFF);
}