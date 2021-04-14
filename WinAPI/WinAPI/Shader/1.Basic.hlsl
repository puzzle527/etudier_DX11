
struct VertexInput
{
    //멤버변수
    //              : 시멘틱 (사용용도)
    float4 Position : POSITION0;
    //float2 TexCoord : TEXCOORD0;
    float4 Color : COLOR0;
};
// PI
struct PixelInput
{
    float4 Position : SV_POSITION; //화면좌표계 포지션
    //float2 TexCoord : TEXCOORD0;
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
//픽셀쉐이더에서 쓸 상수버퍼 컬러
//cbuffer PS_COLOR : register(b0)
//{
//    //4 개의 4바이트
//    float4 Color;
//}

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
    output.Color = input.Color;
    //output.TexCoord = input.TexCoord;

    return output;
}
//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET 은 타겟이될 색깔 
{
   
    //            r  g  b  a
    //return float4(1, 0, 0,1);
    return input.Color;
}