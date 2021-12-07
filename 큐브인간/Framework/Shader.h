#pragma once
class Shader
{
    ID3D11InputLayout*  vertexLayout;
    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader*  pixelShader;
public:
    VertexType vertextype;
    string file;
    Shader();
    ~Shader();
    void LoadFile(string file, VertexType vertextype);
    void Set();
};
