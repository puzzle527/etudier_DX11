#pragma once
class Image : public Object
{
private:
    //그냥 평범한 d3d버퍼
    ID3D11Buffer*   VertexBuffer;
    UINT			VertexCount;//정점갯수
    VertexPT*       Vertex;
    //           쉐이더자원뷰
    //자원뷰들은 파이프라인에 자원을 연결할때
    ID3D11ShaderResourceView* srv;
    ID3D11Buffer*   UVBuffer; //갱신할 이미지좌표버퍼
public:
    //                     최소값     최대값
    Vector4         UV{ 0.0f ,0.0f ,1.0f,1.0f };


    Image(_tstring file, Vector2 pivot = Vector2(0.0f, 0.0f));
    ~Image();
    //중심을 어디에 두고 찍을건가?

    void Init()override;
    void WorldUpdate()override;
    void Render()override;
};

