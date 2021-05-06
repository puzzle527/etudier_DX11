//hlsl�� ���� ã�ƺ���
//���̴� å ���� �о��
struct VertexInput
{
    //�������
    //              : �ø�ƽ (���뵵)
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};
// PI
struct PixelInput
{
    float4 Position : SV_POSITION; //ȭ����ǥ�� ������
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
//���ؽ����̴����� �� ������� �÷�
cbuffer VS_COLOR : register(b3)
{
    //4 ���� 4����Ʈ
    float4 Color;
}

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
    output.Color =
    //            0 ~ 2  ->   -1 ~ 1
    input.Color + (Color * 2.0f - 1.0f);
    
    //0~1 ���α�
    saturate(output.Color);

    return output;
}
//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET �� Ÿ���̵� ���� 
{
   
    //if (input.Position.y > 300)
    //{
    //    return float4(1, 0, 0, 1);
    //}
    //            r  g  b  a
    //return float4(1, 0, 0,1);
    return input.Color;
}