#pragma once
#include "stdafx.h"
//�׸� �� ��
static bool ColRectPt(Rect* rc, Vector2 Pt)
{
    if (!rc->isActive) return false;

    //����� ���ϱ�
    Matrix Inverse;
    D3DXMatrixInverse(&Inverse, NULL, &rc->RT);

    //���� ������ ��Ʈ�� �������� ���̵�
    D3DXVec2TransformCoord(
        &Pt, &Pt, &Inverse);
    //   V = V * RT-1

    Vector2 HalfScale = rc->Scale * 0.5f;

    //��� ���� ���ϱ�
    Vector2 Pos = Vector2(-rc->Pivot.x * rc->Scale.x,
        -rc->Pivot.y * rc->Scale.y);


    if (Pos.x - HalfScale.x < Pt.x &&
        Pt.x < Pos.x + HalfScale.x &&
        Pos.y - HalfScale.y < Pt.y &&
        Pt.y < Pos.y + HalfScale.y)
    {
        return true;
    }
    return false;
}
//���� ��
static bool ColCirPt(Circle* cc, Vector2 Pt)
{
    if (!cc->isActive) return false;

    float Radius = cc->Scale.x * 0.5f;
    Vector2 Pos = cc->GetWorldPos() - cc->WorldPivot;
    
    //�Ѱ��� ���� ���� ���ϱ�
    Vector2 Dis = Pt - Pos;
    //���� ���� ���ϱ�
    float len = Length(&Dis);
    //�������� ���� ��
    if (len < Radius)
    {
        return true;
    }
    return false;

}

//���� ��
static bool ColCir(Circle* cc1, Circle* cc2)
{
    if (!cc1->isActive || !cc2->isActive) return false;

    float HalfScale = cc1->Scale.x * 0.5f + cc2->Scale.x * 0.5f;

    Vector2 Pos1 = cc1->GetWorldPos() - cc1->WorldPivot;
    Vector2 Pos2 = cc2->GetWorldPos() - cc2->WorldPivot;
    Vector2 Dis = Pos1 - Pos2;
    float len = Length(&Dis);

    if (len < HalfScale)
    {
        return true;
    }
    return false;
}
//���� �簢�� �浹
static bool ColRectCir(Rect* rc, Circle* cc)
{
    if (!cc->isActive || !rc->isActive) return false;
    //���� �߽���
    Vector2 CirPos
        = cc->GetWorldPos() - cc->WorldPivot;
    //����� ���ϱ�
    Matrix Inverse;
    D3DXMatrixInverse(&Inverse, NULL, &rc->RT);

    //���� ���߽����� ��Ʈ�� �������� ���̵�
    D3DXVec2TransformCoord(
        &CirPos, &CirPos, &Inverse);
    //�׸��� ����ũ�Ⱚ
    Vector2 HalfScale = rc->Scale * 0.5f;
    //�׸��� �߽ɰ�
    Vector2 RectPos = Vector2(-rc->Pivot.x * rc->Scale.x,
        -rc->Pivot.y * rc->Scale.y);
    //���� ������
    float Radius = cc->Scale.x * 0.5f;
    //Ȯ��� �簢�� 2��
    //���ΰ� Ȯ��� �簢��
    if (RectPos.x - HalfScale.x - Radius < CirPos.x &&
        CirPos.x < RectPos.x + HalfScale.x + Radius &&
        RectPos.y - HalfScale.y < CirPos.y &&
        CirPos.y < RectPos.y + HalfScale.y)
    {
        return true;
    }
    //���ΰ� Ȯ��� �簢��
    if (RectPos.x - HalfScale.x < CirPos.x &&
        CirPos.x < RectPos.x + HalfScale.x &&
        RectPos.y - HalfScale.y - Radius < CirPos.y &&
        CirPos.y < RectPos.y + HalfScale.y + Radius)
    {
        return true;
    }
    //�𼭸� ��
    Vector2 edge[4];
    //���ϴ�
    edge[0] = Vector2(RectPos.x - HalfScale.x,
        RectPos.y - HalfScale.y);
    //�»��
    edge[1] = Vector2(RectPos.x - HalfScale.x,
        RectPos.y + HalfScale.y);
    //����
    edge[2] = Vector2(RectPos.x + HalfScale.x,
        RectPos.y + HalfScale.y);
    //���ϴ�
    edge[3] = Vector2(RectPos.x + HalfScale.x,
        RectPos.y - HalfScale.y);

    //���� �� �浹
    for (int i = 0; i < 4; i++)
    {
        Vector2 Dis = edge[i] - CirPos;
        float len = Length(&Dis);
        if (len < Radius)
        {
            return true;
        }
    }

    //��������Դٸ� �浹�� �ƴϴ�.
    return false;
}

//�׸�� �׸�
static bool AABB(Rect* rc1, Rect* rc2)
{
    if (!rc2->isActive || !rc1->isActive) return false;
    //�߽���
    Vector2 rc1Pos =
        rc1->GetWorldPos() - rc1->WorldPivot;
    Vector2 rc2Pos =
        rc2->GetWorldPos() - rc2->WorldPivot;

    //�׸��� ����ũ�Ⱚ
    Vector2 rc1Half = rc1->Scale * 0.5f;
    Vector2 rc2Half = rc2->Scale * 0.5f;
   
    if (rc1Pos.x - rc1Half.x < rc2Pos.x + rc2Half.x &&
        rc1Pos.x + rc1Half.x > rc2Pos.x - rc2Half.x &&
        rc1Pos.y - rc1Half.y < rc2Pos.y + rc2Half.y &&
        rc1Pos.y + rc1Half.y > rc2Pos.y - rc2Half.y)
    {
        return true;
    }
    return false;
}
static bool OBB(Rect* rc1, Rect* rc2)
{
    //�߽���
    Vector2 rc1Pos =
        rc1->GetWorldPos() - rc1->WorldPivot;
    Vector2 rc2Pos =
        rc2->GetWorldPos() - rc2->WorldPivot;
    //�� �߽������� ���� ����
    Vector2 Dis = rc1Pos - rc2Pos;
    //�簢������ 2���� ����ũ���� ����

    Vector2 Rc1Up =
        rc1->Up * rc1->Scale.y * 0.5f;
    Vector2 Rc1Right =
        rc1->Right * rc1->Scale.x * 0.5f;

    Vector2 Rc2Up =
        rc2->Up * rc2->Scale.y * 0.5f;
    Vector2 Rc2Right =
        rc2->Right * rc2->Scale.x * 0.5f;

    //rc1�� right�� ��
    float dis = fabs(D3DXVec2Dot(&Dis, &rc1->Right));

    //rc2���� �κ��Ͱ� ������ ����
    float v1 = fabs(D3DXVec2Dot(&Rc2Up, &rc1->Right))
        + fabs(D3DXVec2Dot(&Rc2Right, &rc1->Right));
    //rc1���� �κ��Ͱ� ������ ����
    float v2 = rc1->Scale.x * 0.5f;

    if (dis > v1 + v2)return false;

    //rc1�� Up�� ��
    dis = fabs(D3DXVec2Dot(&Dis, &rc1->Up));

    //rc2���� �κ��Ͱ� ������ ����
    v1 = fabs(D3DXVec2Dot(&Rc2Up, &rc1->Up))
        + fabs(D3DXVec2Dot(&Rc2Right, &rc1->Up));
    //rc1���� �κ��Ͱ� ������ ����
    v2 = rc1->Scale.y * 0.5f;

    if (dis > v1 + v2)return false;


    //rc2�� right�� ��
    dis = fabs(D3DXVec2Dot(&Dis, &rc2->Right));

    //rc2���� �κ��Ͱ� ������ ����
    v1 = fabs(D3DXVec2Dot(&Rc1Up, &rc2->Right))
        + fabs(D3DXVec2Dot(&Rc1Right, &rc2->Right));
    //rc1���� �κ��Ͱ� ������ ����
    v2 = rc2->Scale.x * 0.5f;

    if (dis > v1 + v2)return false;

    //rc2�� Up�� ��
    dis = fabs(D3DXVec2Dot(&Dis, &rc2->Up));

    //rc2���� �κ��Ͱ� ������ ����
    v1 = fabs(D3DXVec2Dot(&Rc1Up, &rc2->Up))
        + fabs(D3DXVec2Dot(&Rc1Right, &rc2->Up));
    //rc1���� �κ��Ͱ� ������ ����
    v2 = rc2->Scale.y * 0.5f;

    if (dis > v1 + v2)return false;

    //���� �浹��
    return true;
}