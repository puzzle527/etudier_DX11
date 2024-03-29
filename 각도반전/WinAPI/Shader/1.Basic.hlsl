// HLSL 고오급 쉐이더 언어
//c++이랑 다른언어
//?? 굳이 이걸 써야하는 이유?
//gpu연산이 훨씬 빠르고 gpu를 통할때 쉐이더를 통해 연산이가능


struct VertexInput
{
    //멤버변수
    //              : 시멘틱[n] (사용용도)
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};
// PI
struct PixelInput
{
    float4 Position : SV_POSITION; //화면좌표계 포지션
    float4 Color : COLOR0;
};

//상수버퍼 크기는 16byte배수로 만들어야한다.

//어떤 레지스터에 바인드 되는데 그게 고정되어있다.
cbuffer VS_W : register(b0) //register(b0) 이게 상수 b0위치
{
    //14,24,34 에 위치값이 담긴 매트릭스를 바로 못써서
    //전치행렬 관계의 행렬을 쓰게 row_major
    row_major matrix World;
}
cbuffer VS_V : register(b1)
{
    row_major matrix View;
}
cbuffer VS_P : register(b2)
{
    row_major matrix Proj;
}
cbuffer VS_COLOR : register(b3)
{
    //4 개의 4바이트
    float4 Color;
}

//버텍스 쉐이더
//반환형  함수이름(매개변수)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //공간변환이 있을 예정인 곳
    PixelInput output;
    //L-W
    output.Position = mul(input.Position, World);
    //W-V
    output.Position = mul(output.Position, View);
    //V-P
    output.Position = mul(output.Position, Proj);
    output.Color = 
    // sour     + dest
    //             0~1->   0~2   -1~1
    input.Color + (Color * 2.0f - 1.0f);

    //0~1을 넘어가는값이 되면 안됨
    saturate(output.Color);
    
    return output;
}
//->pixel  PS   ->color
//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET 은 타겟이될 색깔 
{
    //if (input.Position.y > 300)
    //{
    //    return float4(1, 0, 1, 1);
    //}
    //saturate(1.0f, 2.0f);
    //            r  g  b  a
    //return float4(1, 0, 0,1);
    return input.Color;
}