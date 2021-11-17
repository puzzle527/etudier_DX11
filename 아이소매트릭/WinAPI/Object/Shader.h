#pragma once
class Shader
{
private:

    //���̴� ��뿡 �ʿ��� com �������̽�
    ID3D11VertexShader*			VertexShader;
    ID3D11PixelShader*			PixelShader;
    //������ ���� ��ü (hlsl���������)
    ID3D10Blob*					VsBlob;
    ID3D10Blob*					PsBlob;
    //������ġ����
    ID3D11InputLayout*			VertexLayout;

public:
    Shader(_tstring file, string vs = "VS", string ps = "PS");
    ~Shader();
    void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);
    void SetShader();
};

