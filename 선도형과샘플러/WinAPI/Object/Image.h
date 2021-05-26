#pragma once

enum Sampling
{
    //filter
    _POINT,_LINEAR,
    //address mode
    _CLAMP, _WRAP,_MIRROR
};



class Image : public Object
{
private:
    //�׳� ����� d3d����
    ID3D11Buffer*   VertexBuffer;
    UINT			VertexCount;//��������
    VertexPT*       Vertex;
    //           ���̴��ڿ���
    //�ڿ������ ���������ο� �ڿ��� �����Ҷ�
    ID3D11ShaderResourceView* srv;//t0
    ID3D11SamplerState*     Sampler;//s0
    D3D11_SAMPLER_DESC	    SamplerDesc;

    ID3D11Buffer*   UVBuffer; //������ �̹�����ǥ����
public:
    //                     �ּҰ�     �ִ밪
    Vector4         UV{ 0.0f ,0.0f ,1.0f,1.0f };


    Image(_tstring file, Vector2 pivot = Vector2(0.0f, 0.0f));
    ~Image();
    //�߽��� ��� �ΰ� �����ǰ�?

    void Init()override;
    void WorldUpdate()override;
    void Render()override;
    //���ø� ü����
    void ChangeFilter(Sampling sam);
    void ChangeAddress(Sampling sam);
};

