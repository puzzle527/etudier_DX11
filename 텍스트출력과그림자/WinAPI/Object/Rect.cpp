#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Vector2 pivot, bool isfill)
{
    isFill = isfill;
    //���� ���ִ� �׸�
    if (isFill)
    {
        Vertex = new VertexPC[6];
        VertexCount = 6;
        //�ð�������� �������
        Vertex[0].Position.x = -pivot.x - 0.5f;
        Vertex[0].Position.y = -pivot.y - 0.5f;
        //���
        Vertex[0].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[1].Position.x = -pivot.x - 0.5f;
        Vertex[1].Position.y = -pivot.y + 0.5f;
        //���
        Vertex[1].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[2].Position.x = -pivot.x + 0.5f;
        Vertex[2].Position.y = -pivot.y - 0.5f;
        //������
        Vertex[2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

        Vertex[3].Position.x = -pivot.x - 0.5f;
        Vertex[3].Position.y = -pivot.y + 0.5f;
        //���
        Vertex[3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex[4].Position.x = -pivot.x + 0.5f;
        Vertex[4].Position.y = -pivot.y + 0.5f;
        //�Ķ���
        Vertex[4].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

        Vertex[5].Position.x = +0.5f - pivot.x;
        Vertex[5].Position.y = -0.5f - pivot.y;
        //�Ķ���
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
    //�����ǵ� ��Ÿ�� ȣ��ɶ�
   //�θ��Լ��� ȣ��
    Object::WorldUpdate();

}

void Rect::Render()
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
        (D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    }
    //���� �ѱ�
    g_DeviceContext->OMSetBlendState(g_BlendState[1], NULL, 0xFF);
    g_DeviceContext->Draw(VertexCount, 0);
    //���� ����
    g_DeviceContext->OMSetBlendState(g_BlendState[0], NULL, 0xFF);
}