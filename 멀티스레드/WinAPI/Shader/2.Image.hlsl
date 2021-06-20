
struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
};
// PI
struct PixelInput
{
    float4 Position : SV_POSITION; //화면좌표계 포지션
    float2 Uv : UV0; //매핑된 좌표
    float4 Color : COLOR0; //섞을색상
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
//버텍스쉐이더에서 쓸 상수버퍼 컬러
cbuffer VS_COLOR : register(b3)
{
    //4 개의 4바이트
    float4 Color;
}
cbuffer VS_UV : register(b4)
{
    float4 Uv;
}
//픽셀쉐이더 상수버퍼
cbuffer PS_LIGHT : register(b0)
{
    float2 ScreenPos; //스크린좌표
    float Radius; //반지름크기
    float Padding; //남는값
    float4 LightColor; //조명 색
};



//버텍스 쉐이더
//반환형  함수이름(매개변수)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //공간변환이 있을 예정인 곳
    PixelInput output;
    //output.Position * input.Position;
    //L-W
    output.Position = mul(input.Position, World);
    //W-V
    output.Position = mul(output.Position, View);
    //V-P
    output.Position = mul(output.Position, Proj);
    
    output.Color = Color;
    
    //매핑된 좌표 사용
    output.Uv = input.Uv;
    
    //이미지 x좌표 최소값
    if (output.Uv.x == 0.0f)
    {
        output.Uv.x = Uv.x;
    }
    //x좌표 최대값
    else if (output.Uv.x != 0.0f)
    {
        output.Uv.x = Uv.z;
    }
     //이미지 y좌표 최소값
    if (output.Uv.y == 0.0f)
    {
        output.Uv.y = Uv.y;
    }
    //y좌표 최대값
    else if (output.Uv.y != 0.0f)
    {
        output.Uv.y = Uv.w;
    }
    
    
    
    return output;
}

//텍스쳐 자원  (srv) 에서 연결
Texture2D Texture : register(t0);

//추출기
SamplerState Sampler : register(s0);


//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET 은 타겟이될 색깔 
{
    float4 TextureColor =
    // 매핑된 좌표로 텍스쳐 로드
    Texture.Sample(Sampler, input.Uv);
    
    //읽어온 그림파일의 픽셀색상을 조건문으로 비교
    if (TextureColor.r == 1.0f &&
        TextureColor.g == 0.0f &&
        TextureColor.b == 1.0f)
    {
        TextureColor.a = 0.0f;
    }
    
    TextureColor =
    //            0 ~ 2  ->   -1 ~ 1
    TextureColor + (input.Color * 2.0f - 1.0f);
    
    saturate(TextureColor);
    
    
    //여기서 부터 조명
    float2 Minus = input.Position.xy - ScreenPos;
    float dis = Minus.x * Minus.x + Minus.y * Minus.y;
    dis = sqrt(dis);
    TextureColor =
    TextureColor + (LightColor * 2.0f - 1.0f);
    saturate(TextureColor);
    
    //1번조명
    //if (dis > Radius)
    //{
    //    return float4(0, 0, 0, 1);
    //}
    
    
    //2번조명 가운데가 밝고 갈수록어두워지는
    float temp = 1.0f - saturate(dis / Radius);
    TextureColor.rgb =
    TextureColor.rgb * temp;

    return TextureColor;
}