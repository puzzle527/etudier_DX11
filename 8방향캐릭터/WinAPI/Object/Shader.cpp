#include "stdafx.h"
#include "Shader.h"

Shader::Shader(_tstring file, string vs, string ps)
{
    //Create Shader
    {
        HRESULT hr;

        hr = D3DX11CompileFromFile(file.c_str(),//�о�� ���̴�����
            0,//Ư���� ������ ����
            0,//��Ŭ��� ���� �ʿ��Ҷ� 
            vs.c_str(),//���̴� ���� �Լ���
                       //Effect File�� ���ǵ� technique passes�� 
                       //	Shader Entry Point �� ���� �Ǿ� �����Ƿ� �� Parameter�� NULL�� �����Ѵ�.
            "vs_5_0",//���̴� ����
            0,//Shader Code �� Compile ��Ŀ� ������ ��ġ�� Flags�� �����Ѵ�.
            0, //Ư���� ������ �����Ƿ� 0�� �����Ѵ�.
            0, //Shader�� �񵿱������� Compile �ϱ� ���� Option ���� ���ȴ�.
            &VsBlob,//Compile�� Shader�� ���� ID3D10Blob(COM ��ü���� ���) Structure �� ����Ű�� Pointer
            0,//Error Message�� ���� ID3D10Blobk(���� COM ��ü���� ���) Structure�� ����Ű�� Pointer
            0);//�񵿱� Compile�� Error Code �� ��ȸ�ϴµ� ���δ�
               /*�񵿱� �������� �������� ���� ��쿡�� �����ϰ� 0�� �����Ѵ�.
               �� �ƹ��͵� �������� �ʴ´�.*/
        assert(SUCCEEDED(hr));

        hr = D3DX11CompileFromFile(file.c_str(), 0, 0, ps.c_str(), "ps_5_0", 0, 0, 0, &PsBlob, 0, 0);
        assert(SUCCEEDED(hr));


        hr = g_Device->CreateVertexShader(VsBlob->GetBufferPointer(), //������ �� ���̴��� ���� ������.
            VsBlob->GetBufferSize()//������ �� ���ؽ� ���̴��� ũ��
            , NULL, //Ŭ���� ���� �������̽��� ���� ������ ( ID3D11ClassLinkage ���� ); ���� NULL �� �� �ֽ��ϴ� .
            &VertexShader);//ID3D11VertexShader �������̽� �� ���� �������� �ּ��Դϴ�
        assert(SUCCEEDED(hr));

        hr = g_Device->CreatePixelShader(PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(), NULL, &PixelShader);
        assert(SUCCEEDED(hr));



    }

}

Shader::~Shader()
{
    SAFE_RELEASE(VertexShader);
    SAFE_RELEASE(PixelShader);
    SAFE_RELEASE(VsBlob);
    SAFE_RELEASE(PsBlob);
    SAFE_RELEASE(VertexLayout);
}

void Shader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC * desc, UINT count)
{
    //Create InputLayout
    {
        HRESULT hr = g_Device->CreateInputLayout
        (
            desc,//��������ü�迭
            count,//�迭���Ұ���
            VsBlob->GetBufferPointer(),//�������̴� ������
            VsBlob->GetBufferSize(),//���̴�ũ��
            &VertexLayout//�Է¹�ġ�� �����͸� ���� ������
        );
        assert(SUCCEEDED(hr));
    }
}

void Shader::SetShader()
{
    //���������ο� ���ε�
    g_DeviceContext->VSSetShader(VertexShader,//������ ���̴��� ����Ű�� ������ ( ID3D11VertexShader ���� ) NULL�� ���� �ϸ��� ������ ���� �ܰ迡 ���� ���̴��� ��Ȱ��ȭ�˴ϴ�.
        0, //Ŭ���� �ν��Ͻ� �������̽��� �迭�� ���� �������Դϴ� ,���̴��� �������̽��� ������� �ʴ� ��� ppClassInstances�� NULL�� �����Ͻʽÿ� .
        0);//�迭�� Ŭ���� �ν��Ͻ� �������̽� ���Դϴ�
    g_DeviceContext->PSSetShader(PixelShader,//�ȼ� ���̴��� ������ 
        0, 0);
    g_DeviceContext->IASetInputLayout(VertexLayout);
}
