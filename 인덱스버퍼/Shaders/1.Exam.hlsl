
struct VertexInput
{
    float4 Position : POSITION0;
};
struct PixelInput
{
    float4 Position : SV_POSITION; 
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
    //output.Position = input.Position;
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    if (input.Position.y <400)
    {
        return float4(1, 0, 0, 1);
    }

    return float4(0, 0, 0, 1);
}