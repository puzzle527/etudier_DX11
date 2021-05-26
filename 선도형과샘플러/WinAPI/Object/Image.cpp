#include "stdafx.h"
#include "Image.h"

Image::Image(_tstring file, Vector2 pivot)
{
    _tstring textureFile = _T("./Images/") + file;

    HRESULT hr;

    //jpg,png,gif,bmp ������ �ҷ��ü�����
    D3DX11CreateShaderResourceViewFromFile
    (
        g_Device,//����̽�
        textureFile.c_str(),//�����̸�
        NULL, //�߰����� �̹��� ���� NULL���� ����ũ��
        NULL,//�ΰ�
        &srv,//���̴��ڿ���
        &hr
    );
    assert(SUCCEEDED(hr) && "�ؽ��ķε� ����");

    //�⺻ ���÷� ��
    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // �Ҽ��� ������
    //SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; //�������� ����

    //0~1 ���̰��� ����� ��ǥ�� ����Ҷ� �ٲٴ� �ɼ�
    //D3D11_TEXTURE_ADDRESS_CLAMP ������ �ȼ������� ���� ä���.
    //D3D11_TEXTURE_ADDRESS_WRAP 0 1 �Ѿ�°� �ٽ� 0~1������ ���д�.
    //D3D11_TEXTURE_ADDRESS_MIRROR 0 1 �Ѿ�°� ����� 0~1������ ���д�.
    SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    SamplerDesc.MipLODBias = 0.0f;
    SamplerDesc.MaxAnisotropy = 1;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    SamplerDesc.MinLOD = -FLT_MAX;
    SamplerDesc.MaxLOD = FLT_MAX;

    //�ϳ� �̻��� ���÷� ����� �α�
    g_Device->CreateSamplerState(&SamplerDesc, &Sampler);






    Vertex = new VertexPT[6];
    VertexCount = 6;
    //�ð�������� �������
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
    //������
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
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPT) * VertexCount; //���� ũ�� (����Ʈ)�Դϴ�.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���۰� ������ ���ο� ���ε��Ǵ� ����� �ĺ��Ͻʽÿ�

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //���� ���ҽ��� �ʱ�ȭ�ϱ����� �����͸� �����մϴ�.
        data.pSysMem = Vertex;
        //�ʱ�ȭ �������� ������.

        //���� �����
        HRESULT hr = g_Device->CreateBuffer(&desc, &data, &VertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Vector4);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�������
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &UVBuffer);
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
        { "UV",//�ø�ƽ���� ������ �ڷ���
        0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
        DXGI_FORMAT_R32G32_FLOAT,//3���� 32��Ʈ float����
        0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
        12,//������ R32G32B32 4 ,4,4 ->12
        D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
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
    SAFE_RELEASE(UVBuffer);
    SAFE_RELEASE(Sampler);
    SAFE_RELEASE(srv);
}

void Image::Init()
{
    Object::Init();
}

void Image::WorldUpdate()
{
    if (!isActive)return;
    //�����ǵ� ��Ÿ�� ȣ��ɶ�
   //�θ��Լ��� ȣ��
    Object::WorldUpdate();
}

void Image::Render()
{
    if (!isActive)return;
    Object::Render();

    shader->SetShader();

    UINT stride = sizeof(VertexPT);
    UINT offset = 0;

    //�ȼ����̴��� ���̴��ڿ��� ����
    g_DeviceContext->PSSetShaderResources(0,// ����ɷ������� ��ȣ 0
        1,//���ҽ�����
        &srv);
    //����ɷ������� ��ȣ 0
    g_DeviceContext->PSSetSamplers(0,
        1, //���ҽ�����
        &Sampler);//���÷�

    g_DeviceContext->UpdateSubresource(UVBuffer, 0, NULL, &UV, 0, 0);
    //                            ����ɷ������� ��ȣ4
    g_DeviceContext->VSSetConstantBuffers(4, 1, &UVBuffer);




    g_DeviceContext->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
        1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
        &VertexBuffer,
        &stride,//���������� �� ������ ����Ʈ���� ũ��
        &offset);
    //������ ��������
    g_DeviceContext->IASetPrimitiveTopology
    (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //���� �ѱ�
    g_DeviceContext->OMSetBlendState(g_BlendState[1], NULL, 0xFF);
    g_DeviceContext->Draw(VertexCount, 0);
    //���� ����
    g_DeviceContext->OMSetBlendState(g_BlendState[0], NULL, 0xFF);
}

void Image::ChangeFilter(Sampling sam)
{
    if (sam == _POINT)
    {
        SamplerDesc.Filter =
            D3D11_FILTER_MIN_MAG_MIP_POINT;
        //���� ���÷� ����
        SAFE_RELEASE(Sampler);
        //���� �ٽ� �����
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _LINEAR)
    {
        SamplerDesc.Filter =
            D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        SAFE_RELEASE(Sampler);
        //���� �ٽ� �����
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
        //���� �ٽ� �����
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _WRAP)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

        SAFE_RELEASE(Sampler);
        //���� �ٽ� �����
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _MIRROR)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
        SAFE_RELEASE(Sampler);
        //���� �ٽ� �����
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
}
