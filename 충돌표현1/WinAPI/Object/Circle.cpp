#include "stdafx.h"
#include "Circle.h"

Circle::Circle(UINT slice, Vector2 pivot)
{
    this->Slice = slice;

    float Seta = 2.0f * PI / (float)Slice;

    //36�����϶� �ﰢ�� �? 36
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

    //���� ����
    D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
    {
        { "POSITION",//�ø�ƽ���� ������ �ڷ���
        0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
        DXGI_FORMAT_R32G32B32_FLOAT,//3���� 32��Ʈ float����
        0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
        0,//�� ��Ұ� �޸𸮵�� ������������ �󸶳� ������ ��ġ�� �ִ°��� �˷��ش�.ó������0
        D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
        0 },//�Ѿ��
    { "COLOR",//�ø�ƽ���� ������ �ڷ���
    0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
    DXGI_FORMAT_R32G32B32_FLOAT,//3���� 32��Ʈ float����
    0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
    12,//������ R32G32B32 4 ,4,4 ->12
    D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
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
    g_DeviceContext->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
        1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
        &VertexBuffer,
        &stride,//���������� �� ������ ����Ʈ���� ũ��
        &offset);

    //������ ��������
    g_DeviceContext->IASetPrimitiveTopology
    (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);


    //DrawCall
    g_DeviceContext->Draw(VertexCount, 0);
}
