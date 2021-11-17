#pragma once


enum Animation
{
    _STOP,      //정지
    _LOOP, _MIRRORLOOP,// 반복재생
    _ONCE, _MIRRORONCE,// 한번재생
};

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
    //그냥 평범한 d3d버퍼
    ID3D11Buffer*   VertexBuffer;
    UINT			VertexCount;//정점갯수
    VertexPT*       Vertex;
    //           쉐이더자원뷰
    //자원뷰들은 파이프라인에 자원을 연결할때
    ID3D11ShaderResourceView*   srv;//t0
    ID3D11SamplerState*         Sampler;//s0
    D3D11_SAMPLER_DESC	        SamplerDesc;

    ID3D11Buffer*               UVBuffer; //갱신할 이미지좌표버퍼

    //애니메이션 멤버
    float           AnimTime = 0.0f;    //재생시간경과량
    Animation       AnimState = _STOP;  //재생상태
    bool            AnimXAxis = true;   //가로재생?
    float           AnimInterval = 0.0f;//재생간격
    //내부에서 재생할때 호출할 함수
    void            PlayAnim();
public:
    //                     최소값     최대값
    Vector4         UV{ 0.0f ,0.0f ,1.0f,1.0f };
    Int2      MaxFrame{ 1,1 };  //분할사이즈
    Int2      Frame{ 0,0 };     //분할된 좌표

    Image(_tstring file, Vector2 pivot = Vector2(0.0f, 0.0f));
    ~Image();
    //중심을 어디에 두고 찍을건가?

    void Init()override;
    void WorldUpdate()override;
    void Render()override;
    //샘플링 체인지
    void ChangeFilter(Sampling sam);
    void ChangeAddress(Sampling sam);
    //애니메이션 함수             
    void ChangeAnim(Animation anim,
        // 얼마간격인가?
        float interval, bool XAxis = true);
    MAKEGET(Animation ,AnimState)
};

