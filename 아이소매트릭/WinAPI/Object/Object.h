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

    

    Shader*				shader;  //���̴�
    ID3D11Buffer*		WBuffer; //�ڿ�
    ID3D11Buffer*		ColorBuffer;

public:
    //Ȱ��ȭ�� ������Ʈ �ΰ�?
    bool        isActive = true;
    Vector2		Pivot = Vector2(0, 0);
    Vector2     WorldPivot;
    Matrix  RT; //ȸ���̵����
    Matrix* P; // �θ����
    static Line*  Axis; //��,����
    bool    isAxis = false; //���� �׸��ų�?
    Vector2 Up, Right; //����
    Vector2 Position;//��ġ��,���� (����)
    Vector2 Scale; //ũ��
    Vector3 Rotation; //������ (x,y,z ��)
    Vector3 Rotation2;//������
    //������ ��
    Color   color = Color(0.5f, 0.5f, 0.5f, 0.5f);


    Object();
    virtual ~Object();
    virtual void Init();
    virtual void WorldUpdate();
    virtual void Render();
    Vector2 GetWorldPos() { return Vector2(W._41, W._42); }
};

