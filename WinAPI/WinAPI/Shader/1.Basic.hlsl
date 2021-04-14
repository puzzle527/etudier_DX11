
struct VertexInput
{
    //�������
    //              : �ø�ƽ (���뵵)
    float4 Position : POSITION0;
    //float2 TexCoord : TEXCOORD0;
    float4 Color : COLOR0;
};
// PI
struct PixelInput
{
    float4 Position : SV_POSITION; //ȭ����ǥ�� ������
    //float2 TexCoord : TEXCOORD0;
    float4 Color : COLOR0;
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
//�ȼ����̴����� �� ������� �÷�
//cbuffer PS_COLOR : register(b0)
//{
//    //4 ���� 4����Ʈ
//    float4 Color;
//}

//���ؽ� ���̴�
//��ȯ��  �Լ��̸�(�Ű�����)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
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
//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET �� Ÿ���̵� ���� 
{
   
    //            r  g  b  a
    //return float4(1, 0, 0,1);
    return input.Color;
}