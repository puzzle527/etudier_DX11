#include "Framework.h"
#include "Shader.h"

Shader::Shader()
{
    
}

Shader::~Shader()
{
    SafeRelease(vertexLayout);
    SafeRelease(vertexShader);
    SafeRelease(pixelShader);
}

void Shader::LoadFile(string file, VertexType vertextype)
{
    //컴파일결과를 담아놓는 인터페이스
    ID3D10Blob* VsBlob;
    ID3D10Blob* PsBlob;

    wstring path = L"../Shaders/"+ String::ToWString(file) +L".hlsl";

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS", "vs_5_0", flags, 0, &VsBlob, nullptr);

    D3D->GetDevice()->CreateVertexShader(VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(),
        nullptr, &vertexShader);


    switch (vertextype)
    {
    case VertexType::V_P:
         D3D->GetDevice()->CreateInputLayout
         (
             VertexP::LayoutDesc,
             1,
             VsBlob->GetBufferPointer(),
             VsBlob->GetBufferSize(),
             &vertexLayout
         );
        break;
    case VertexType::V_PC:
    
        D3D->GetDevice()->CreateInputLayout
        (
            VertexPC::LayoutDesc,
            2,
            VsBlob->GetBufferPointer(),
            VsBlob->GetBufferSize(),
            &vertexLayout
        );
        break;
    }

    


    

    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS", "ps_5_0", flags, 0, &PsBlob, nullptr);

    D3D->GetDevice()->CreatePixelShader(PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(),
        nullptr, &pixelShader);

    SafeRelease(VsBlob);
    SafeRelease(PsBlob);
}

void Shader::Set()
{
    D3D->GetDC()->VSSetShader(vertexShader, 0, 0);
    D3D->GetDC()->PSSetShader(pixelShader, 0, 0);
    D3D->GetDC()->IASetInputLayout(vertexLayout);
}
