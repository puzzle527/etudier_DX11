#include "stdafx.h"
#include "Circle.h"

Circle::Circle(UINT slice, Vector2 pivot, bool isfill)
{
    isFill = isfill;
    this->Slice = slice;

    float Seta = 2.0f * PI / (float)Slice;
    if (isFill)
    {
        //36�����϶� �ﰢ�� �? 36
        VertexCount = Slice * 3;

        Vertex = new VertexPC[VertexCount];
        //RenderVertex = new Vector2[Slice];

        for (UINT i = 0; i < Slice; i++)
        {
            Vertex[i * 3].Position.x = 0.0f - pivot.x;
            Vertex[i * 3].Position.y = 0.0f - pivot.y;
            Vertex[i * 3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            Vertex[i * 3 + 1].Position.x = cosf(Seta * (i + 1)) * 0.5f - pivot.x;
            Vertex[i * 3 + 1].Position.y = sinf(Seta * (i + 1)) * 0.5f - pivot.y;

            Vertex[i * 3 + 1].color =
                Color(0.0f, 0.0f, 0.0f, 1.0f);
            Vertex[i * 3 + 2].Position.x = cosf(Seta * (i)) * 0.5f - pivot.x;
            Vertex[i * 3 + 2].Position.y = sinf(Seta * (i)) * 0.5f - pivot.y;

            Vertex[i * 3 + 2].color =
                Color(0.0f, 0.0f, 0.0f, 1.0f);
            //Vertex[i].x = cosf(Seta*i)*0.5f;
            //Vertex[i].y = sinf(Seta*i)*0.5f;
        }

    }
    else
    {
        VertexCount = Slice * 2;
        Vertex = new VertexPC[VertexCount];


        for (UINT i = 0; i < Slice; i++)
        {
           
            Vertex[i * 2].Position.x = cosf(Seta * (i + 1)) * 0.5f - pivot.x;
            Vertex[i * 2].Position.y = sinf(Seta * (i + 1)) * 0.5f - pivot.y;
                       
            Vertex[i * 2].color =
                Color(1.0f, 1.0f, 1.0f, 1.0f);
            Vertex[i *2 + 1].Position.x = cosf(Seta * (i)) * 0.5f - pivot.x;
            Vertex[i *2 + 1].Position.y = sinf(Seta * (i)) * 0.5f - pivot.y;
                          
            Vertex[i *2 + 1].color =
                Color(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
    
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * VertexCount; //���� ũ�� (����Ʈ)�Դϴ�.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���۰� ������ ���ο� ���ε��Ǵ� ����� �ĺ��Ͻʽÿ�

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //���� ���ҽ��� �ʱ�ȭ�ϱ����� �����͸� �����մϴ�.
        data.pSysMem = Vertex;
        //�ʱ�ȭ �������� ������.

        //���� �����
        HRESULT hr = g_Device->CreateBuffer(&desc, &data, &VertexBuffer);
        assert(SUCCEEDED(hr));
    }

    shader = RESOURCEMANAGER->ShaderArray[0];
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
    if (!isActive)return;
    Object::WorldUpdate();
}

void Circle::Render()
{
    if (!isActive)return;
    Object::Render();
    shader->SetShader();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;
    g_DeviceContext->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
        1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
        &VertexBuffer,
        &stride,//���������� �� ������ ����Ʈ���� ũ��
        &offset);

    //������ ��������
    if (isFill)
    {
        g_DeviceContext->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
    else
    {
        g_DeviceContext->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    }
   
    //(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);


  //���� �ѱ�
    g_DeviceContext->OMSetBlendState(g_BlendState[1], NULL, 0xFF);
    g_DeviceContext->Draw(VertexCount, 0);
    //���� ����
    g_DeviceContext->OMSetBlendState(g_BlendState[0], NULL, 0xFF);
}
