#pragma once
class Shader
{
    ID3D11InputLayout* vertexLayout;
    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;
public:
    Shader();
    ~Shader();
    void Set();
};
