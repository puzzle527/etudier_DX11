#pragma once
class Transform
{
    //4������ �ð����� ������ 
    //X    w= ����
    //���� x ����� ���Ҷ��� �ʿ�
public:
    Transform();
    Vector3 position; //��ġ
    Vector3 rotation; //ȸ������(3��ȸ����)
    Vector3 scale; //ũ��(����)

    virtual void ImGuiRender();
};

