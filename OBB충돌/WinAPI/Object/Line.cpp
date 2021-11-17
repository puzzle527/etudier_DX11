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
    //������� ������Ʈ W���� WBuffer�� ����
    g_DeviceContext->UpdateSubresource(WBuffer, 0, NULL, &W, 0, 0);
    //                            ����ɷ������� ��ȣ 0
    g_DeviceContext->VSSetConstantBuffers(0, 1, &WBuffer);

    g_DeviceContext->UpdateSubresource(ColorBuffer, 0, NULL, &color, 0, 0);
    //                            ����ɷ������� ��ȣ 3
    g_DeviceContext->VSSetConstantBuffers(3, 1, &ColorBuffer);


    shader->SetShader();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;
    //������ ��������
    g_DeviceContext->IASetPrimitiveTopology
        //(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        (D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    g_DeviceContext->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
        1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
        &VertexBuffer,
        &stride,//���������� �� ������ ����Ʈ���� ũ��
        &offset);

    //���� �ѱ�
    g_DeviceContext->OMSetBlendState(g_BlendState[1], NULL, 0xFF);
    g_DeviceContext->Draw(VertexCount, 0);
    //���� ����
    g_DeviceContext->OMSetBlendState(g_BlendState[0], NULL, 0xFF);

}