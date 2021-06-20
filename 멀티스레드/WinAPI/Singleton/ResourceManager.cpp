#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    {
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

        ShaderArray[0] = new Shader(_T("./Shader/1.Basic.hlsl"));
        UINT ElementCount = ARRAYSIZE(LayoutDesc);
        ShaderArray[0]->CreateInputLayout(LayoutDesc, ElementCount);
    }
    {
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

        ShaderArray[1] = new Shader(_T("./Shader/2.Image.hlsl"));
        UINT ElementCount = ARRAYSIZE(LayoutDesc);
        ShaderArray[1]->CreateInputLayout(LayoutDesc, ElementCount);
    }
}

ResourceManager::~ResourceManager()
{
    SAFE_DELETE(ShaderArray[0]);
    SAFE_DELETE(ShaderArray[1]);
    for (auto i = SrvMap.begin();
        i != SrvMap.end(); i++)
    {
        if (i->second)
        {
            i->second->Release();
        }
    }
    SrvMap.clear();
}

ID3D11ShaderResourceView* ResourceManager::LoadTexture(_tstring file)
{
    if (SrvMap.find(file) != SrvMap.end())
        return SrvMap[file];


    _tstring textureFile = _T("./Images/") + file;

    HRESULT hr;
    ID3D11ShaderResourceView* temp;

    //jpg,png,gif,bmp ������ �ҷ��ü�����
    D3DX11CreateShaderResourceViewFromFile
    (
        g_Device,//����̽�
        textureFile.c_str(),//�����̸�
        NULL, //�߰����� �̹��� ���� NULL���� ����ũ��
        NULL,//�ΰ�
        &temp,//���̴��ڿ���
        &hr
    );
    assert(SUCCEEDED(hr) && "�ؽ��ķε� ����");

    SrvMap[file] = temp;
    return temp;
}
