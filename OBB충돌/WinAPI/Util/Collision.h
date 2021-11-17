#pragma once
#include "stdafx.h"
//네모 와 점
static bool ColRectPt(Rect* rc, Vector2 Pt)
{
    if (!rc->isActive) return false;

    //역행렬 구하기
    Matrix Inverse;
    D3DXMatrixInverse(&Inverse, NULL, &rc->RT);

    //들어온 정점이 렉트를 기준으로 역이동
    D3DXVec2TransformCoord(
        &Pt, &Pt, &Inverse);
    //   V = V * RT-1

    Vector2 HalfScale = rc->Scale * 0.5f;

    //벗어난 원점 구하기
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
//원과 점
static bool ColCirPt(Circle* cc, Vector2 Pt)
{
    if (!cc->isActive) return false;

    float Radius = cc->Scale.x * 0.5f;
    Vector2 Pos = cc->GetWorldPos() - cc->WorldPivot;
    
    //둘간의 차이 벡터 구하기
    Vector2 Dis = Pt - Pos;
    //벡터 길이 구하기
    float len = Length(&Dis);
    //반지름과 길이 비교
    if (len < Radius)
    {
        return true;
    }
    return false;

}

//원과 원
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
//원과 사각형 충돌
static bool ColRectCir(Rect* rc, Circle* cc)
{
    if (!cc->isActive || !rc->isActive) return false;
    //원의 중심점
    Vector2 CirPos
        = cc->GetWorldPos() - cc->WorldPivot;
    //역행렬 구하기
    Matrix Inverse;
    D3DXMatrixInverse(&Inverse, NULL, &rc->RT);

    //들어온 원중심점이 렉트를 기준으로 역이동
    D3DXVec2TransformCoord(
        &CirPos, &CirPos, &Inverse);
    //네모의 절반크기값
    Vector2 HalfScale = rc->Scale * 0.5f;
    //네모의 중심값
    Vector2 RectPos = Vector2(-rc->Pivot.x * rc->Scale.x,
        -rc->Pivot.y * rc->Scale.y);
    //원의 반지름
    float Radius = cc->Scale.x * 0.5f;
    //확장된 사각형 2개
    //가로가 확장된 사각형
    if (RectPos.x - HalfScale.x - Radius < CirPos.x &&
        CirPos.x < RectPos.x + HalfScale.x + Radius &&
        RectPos.y - HalfScale.y < CirPos.y &&
        CirPos.y < RectPos.y + HalfScale.y)
    {
        return true;
    }
    //세로가 확장된 사각형
    if (RectPos.x - HalfScale.x < CirPos.x &&
        CirPos.x < RectPos.x + HalfScale.x &&
        RectPos.y - HalfScale.y - Radius < CirPos.y &&
        CirPos.y < RectPos.y + HalfScale.y + Radius)
    {
        return true;
    }
    //모서리 점
    Vector2 edge[4];
    //좌하단
    edge[0] = Vector2(RectPos.x - HalfScale.x,
        RectPos.y - HalfScale.y);
    //좌상단
    edge[1] = Vector2(RectPos.x - HalfScale.x,
        RectPos.y + HalfScale.y);
    //우상단
    edge[2] = Vector2(RectPos.x + HalfScale.x,
        RectPos.y + HalfScale.y);
    //우하단
    edge[3] = Vector2(RectPos.x + HalfScale.x,
        RectPos.y - HalfScale.y);

    //원과 점 충돌
    for (int i = 0; i < 4; i++)
    {
        Vector2 Dis = edge[i] - CirPos;
        float len = Length(&Dis);
        if (len < Radius)
        {
            return true;
        }
    }

    //여기까지왔다면 충돌이 아니다.
    return false;
}

//네모와 네모
static bool AABB(Rect* rc1, Rect* rc2)
{
    if (!rc2->isActive || !rc1->isActive) return false;
    //중심점
    Vector2 rc1Pos =
        rc1->GetWorldPos() - rc1->WorldPivot;
    Vector2 rc2Pos =
        rc2->GetWorldPos() - rc2->WorldPivot;

    //네모의 절반크기값
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
    //중심점
    Vector2 rc1Pos =
        rc1->GetWorldPos() - rc1->WorldPivot;
    Vector2 rc2Pos =
        rc2->GetWorldPos() - rc2->WorldPivot;
    //두 중심점간의 차이 벡터
    Vector2 Dis = rc1Pos - rc2Pos;
    //사각형마다 2개의 절반크기의 벡터

    Vector2 Rc1Up =
        rc1->Up * rc1->Scale.y * 0.5f;
    Vector2 Rc1Right =
        rc1->Right * rc1->Scale.x * 0.5f;

    Vector2 Rc2Up =
        rc2->Up * rc2->Scale.y * 0.5f;
    Vector2 Rc2Right =
        rc2->Right * rc2->Scale.x * 0.5f;

    //rc1의 right축 비교
    float dis = fabs(D3DXVec2Dot(&Dis, &rc1->Right));

    //rc2에서 두벡터가 투영된 길이
    float v1 = fabs(D3DXVec2Dot(&Rc2Up, &rc1->Right))
        + fabs(D3DXVec2Dot(&Rc2Right, &rc1->Right));
    //rc1에서 두벡터가 투영된 길이
    float v2 = rc1->Scale.x * 0.5f;

    if (dis > v1 + v2)return false;

    //rc1의 Up축 비교
    dis = fabs(D3DXVec2Dot(&Dis, &rc1->Up));

    //rc2에서 두벡터가 투영된 길이
    v1 = fabs(D3DXVec2Dot(&Rc2Up, &rc1->Up))
        + fabs(D3DXVec2Dot(&Rc2Right, &rc1->Up));
    //rc1에서 두벡터가 투영된 길이
    v2 = rc1->Scale.y * 0.5f;

    if (dis > v1 + v2)return false;


    //rc2의 right축 비교
    dis = fabs(D3DXVec2Dot(&Dis, &rc2->Right));

    //rc2에서 두벡터가 투영된 길이
    v1 = fabs(D3DXVec2Dot(&Rc1Up, &rc2->Right))
        + fabs(D3DXVec2Dot(&Rc1Right, &rc2->Right));
    //rc1에서 두벡터가 투영된 길이
    v2 = rc2->Scale.x * 0.5f;

    if (dis > v1 + v2)return false;

    //rc2의 Up축 비교
    dis = fabs(D3DXVec2Dot(&Dis, &rc2->Up));

    //rc2에서 두벡터가 투영된 길이
    v1 = fabs(D3DXVec2Dot(&Rc1Up, &rc2->Up))
        + fabs(D3DXVec2Dot(&Rc1Right, &rc2->Up));
    //rc1에서 두벡터가 투영된 길이
    v2 = rc2->Scale.y * 0.5f;

    if (dis > v1 + v2)return false;

    //이제 충돌임
    return true;
}