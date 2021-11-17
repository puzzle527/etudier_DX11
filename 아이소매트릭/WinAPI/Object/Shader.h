#pragma once
class Shader
{
private:

    //쉐이더 사용에 필요한 com 인터페이스
    ID3D11VertexShader*			VertexShader;
    ID3D11PixelShader*			PixelShader;
    //컴파일 해줄 객체 (hlsl언어컴파일)
    ID3D10Blob*					VsBlob;
    ID3D10Blob*					PsBlob;
    //정점배치서술
    ID3D11InputLayout*			VertexLayout;

public:
    Shader(_tstring file, string vs = "VS", string ps = "PS");
    ~Shader();
    void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);
    void SetShader();
};

