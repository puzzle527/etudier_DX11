
struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
};
// PI
struct PixelInput
{
    float4 Position : SV_POSITION; //ȭ����ǥ�� ������
    float2 Uv : UV0; //���ε� ��ǥ
    float4 Color : COLOR0; //��������
};

//������� ũ��� 16byte����� �������Ѵ�.

//� �������Ϳ� ���ε� �Ǵµ� �װ� �����Ǿ��ִ�.
cbuffer VS_W : register(b0) //register(b0) �̰� ��� b0��ġ
{
    //14,24,34 �� ��ġ���� ��� ��Ʈ������ �ٷ� ���Ἥ
    //��ġ��� ������ ����� ���� row_major
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
//���ؽ����̴����� �� ������� �÷�
cbuffer VS_COLOR : register(b3)
{
    //4 ���� 4����Ʈ
    float4 Color;
}
cbuffer VS_UV : register(b4)
{
    float4 Uv;
}
//�ȼ����̴� �������
cbuffer PS_LIGHT : register(b0)
{
    float2 ScreenPos; //��ũ����ǥ
    float Radius; //������ũ��
    float Padding; //���°�
    float4 LightColor; //���� ��
};



//���ؽ� ���̴�
//��ȯ��  �Լ��̸�(�Ű�����)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
    PixelInput output;
    //output.Position * input.Position;
    //L-W
    output.Position = mul(input.Position, World);
    //W-V
    output.Position = mul(output.Position, View);
    //V-P
    output.Position = mul(output.Position, Proj);
    
    output.Color = Color;
    
    //���ε� ��ǥ ���
    output.Uv = input.Uv;
    
    //�̹��� x��ǥ �ּҰ�
    if (output.Uv.x == 0.0f)
    {
        output.Uv.x = Uv.x;
    }
    //x��ǥ �ִ밪
    else if (output.Uv.x != 0.0f)
    {
        output.Uv.x = Uv.z;
    }
     //�̹��� y��ǥ �ּҰ�
    if (output.Uv.y == 0.0f)
    {
        output.Uv.y = Uv.y;
    }
    //y��ǥ �ִ밪
    else if (output.Uv.y != 0.0f)
    {
        output.Uv.y = Uv.w;
    }
    
    
    
    return output;
}

//�ؽ��� �ڿ�  (srv) ���� ����
Texture2D Texture : register(t0);

//�����
SamplerState Sampler : register(s0);


//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET �� Ÿ���̵� ���� 
{
    float4 TextureColor =
    // ���ε� ��ǥ�� �ؽ��� �ε�
    Texture.Sample(Sampler, input.Uv);
    
    //�о�� �׸������� �ȼ������� ���ǹ����� ��
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
    
    
    //���⼭ ���� ����
    float2 Minus = input.Position.xy - ScreenPos;
    float dis = Minus.x * Minus.x + Minus.y * Minus.y;
    dis = sqrt(dis);
    TextureColor =
    TextureColor + (LightColor * 2.0f - 1.0f);
    saturate(TextureColor);
    
    //1������
    //if (dis > Radius)
    //{
    //    return float4(0, 0, 0, 1);
    //}
    
    
    //2������ ����� ��� �����Ͼ�ο�����
    float temp = 1.0f - saturate(dis / Radius);
    TextureColor.rgb =
    TextureColor.rgb * temp;

    return TextureColor;
}