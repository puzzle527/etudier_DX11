#include "stdafx.h"
#include "Image.h"


Image::Image(_tstring file, Vector2 pivot)
{
    srv = RESOURCEMANAGER->LoadTexture(file);

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

    //�ִϸ��̼� ��� �Լ�
    PlayAnim();

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

void Image::PlayAnim()
{
    //���Ұ����� 1�̻��϶�
    if (MaxFrame.x != 1 || MaxFrame.y != 1)
    {
        //������ �ƴѰ�쿡��
        if (AnimState != _STOP)
        {
            //�ð� �����
            AnimTime += DeltaTime;
            //������� ������ݺ��� Ŀ����
            if (AnimTime > AnimInterval)
            {
                AnimTime -= AnimInterval;

                //������ ����ΰ�?
                if (AnimXAxis)
                {
                    //������ ���
                    if (AnimState == _LOOP)
                    {
                        Frame.x++;
                        if (Frame.x == MaxFrame.x)Frame.x = 0;
                    }
                    //������ ���
                    else if (AnimState == _MIRRORLOOP)
                    {
                        Frame.x--;
                        if (Frame.x == -1)Frame.x = MaxFrame.x - 1;
                    }
                    //������ ���
                    else if (AnimState == _ONCE)
                    {
                        Frame.x++;
                        if (Frame.x == MaxFrame.x)
                        {
                            AnimState = _STOP;
                            Frame.x = MaxFrame.x - 1;
                        }
                    }
                    //������ ���
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
                //������ ����ΰ�?
                else
                {
                    //������ ���
                    if (AnimState == _LOOP)
                    {
                        Frame.y++;
                        if (Frame.y == MaxFrame.y)Frame.y = 0;
                    }
                    //������ ���
                    else if (AnimState == _MIRRORLOOP)
                    {
                        Frame.y--;
                        if (Frame.y == -1)Frame.y = MaxFrame.y - 1;
                    }
                    //������ ���
                    else if (AnimState == _ONCE)
                    {
                        Frame.y++;
                        if (Frame.y == MaxFrame.y)
                        {
                            AnimState = _STOP;
                            Frame.y = MaxFrame.y - 1;
                        }
                    }
                    //������ ���
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
    AnimTime = 0.0f;    //����ð� 0���� �ʱ�ȭ
    AnimState = anim;   //���°� ����
    AnimXAxis = XAxis;  //����� ����
    AnimInterval = interval; //������� ����
    //�ѹ� ����̶��(��Ʈ �� ���̹����� �̵�)
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
