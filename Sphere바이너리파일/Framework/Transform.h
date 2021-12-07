#pragma once
class Transform
{
    //4������ �ð����� ������ 
    //X    w= ����
    //���� x ����� ���Ҷ��� �ʿ�
    Matrix S, R, T;
public:
    Matrix W;
    Transform();
    static ID3D11Buffer* WBuffer;
    static void CreateBuffer();
    static void ReleaseBuffer();
    Vector3 position; //��ġ
    Vector3 rotation; //ȸ������(3��ȸ����)
    Vector3 scale; //ũ��(����)
    virtual void Update(Matrix* P = nullptr);
    virtual void Set();
    virtual bool ImGuiRender();
};

