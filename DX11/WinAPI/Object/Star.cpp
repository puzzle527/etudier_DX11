#include "stdafx.h"
#include "Star.h"

void Star::Init()
{
    Object::Init();
    //Local
    for(int i = 0; i < 5; i++)
    {
        //                   position   + cos(72*i) * c
        //                            cos(72*i)
        star[i] = Vector2(cos((72 * i) * TORADIAN)*0.5f,
            -sin((72 * i) * TORADIAN)*0.5f);
    }
}

void Star::WorldUpdate()
{
    //재정의된 스타로 호출될때
    //부모함수도 호출
    Object::WorldUpdate();



}
void Star::Render()
{
    Object::Render();
    Vector2 RenderVertex[5];
    for(int i = 0; i < 5; i++)
    {
        //L->W
        //벡터와 행렬의 곱연산을 해주는 함수
        D3DXVec2TransformCoord(
            &RenderVertex[i], &star[i], &W);
    }
    MoveToEx(g_MemDC, RenderVertex[0].x, RenderVertex[0].y, NULL);
    //이동위치에서 다음위치로 선긋기
    LineTo(g_MemDC, RenderVertex[2].x, RenderVertex[2].y);
    LineTo(g_MemDC, RenderVertex[4].x, RenderVertex[4].y);
    LineTo(g_MemDC, RenderVertex[1].x, RenderVertex[1].y);
    LineTo(g_MemDC, RenderVertex[3].x, RenderVertex[3].y);
    LineTo(g_MemDC, RenderVertex[0].x, RenderVertex[0].y);

}

