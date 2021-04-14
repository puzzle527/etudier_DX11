#pragma once
class Line; //���漱��
class Object
{
protected:

    Matrix  T; //�̵����
    Matrix  S; //ũ�����
    Matrix  R; //���� ȸ�����(z��)
    Matrix  R2; //���� ȸ�����(z��)

    Matrix  W; //�������

    Vector2		Pivot = Vector2(0, 0);

    Shader*				shader;  //���̴�
    ID3D11Buffer*		WBuffer; //�ڿ�
    //ID3D11Buffer*		ColorBuffer;

public:
    Matrix  RT; //ȸ���̵����
    Matrix* P; // �θ����
    static Line*  Axis; //��,����
    bool    isAxis = false; //���� �׸��ų�?
    Vector2 Up, Right; //����
    Vector2 Position;//��ġ��,���� (����)
    Vector2 Scale; //ũ��
    float   Rotation; //������
    float   Rotation2;//������
    Object();
    virtual ~Object();
    virtual void Init();
    virtual void WorldUpdate();
    virtual void Render();
    Vector2 GetWorldPos() { return Vector2(W._41, W._42); }
};

