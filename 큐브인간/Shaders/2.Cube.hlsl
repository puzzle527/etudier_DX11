
struct VertexInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR0;
};

cbuffer VS_W : register(b0)
{
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

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Proj);
    output.Color = input.Color;
    //output.Position = input.Position;
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return input.Color;
}