
struct VertexInput
{
    float4 Position : POSITION0;
};
struct PixelInput
{
    float4 Position : SV_POSITION; 
};
//cbuffer VS_W : register(b0)
//{
//    row_major matrix World;
//}

PixelInput VS(VertexInput input)
{
    PixelInput output;
    //output.Position = mul(input.Position, World);
    output.Position = input.Position;
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