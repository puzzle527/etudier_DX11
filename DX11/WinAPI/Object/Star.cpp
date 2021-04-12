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
    //�����ǵ� ��Ÿ�� ȣ��ɶ�
    //�θ��Լ��� ȣ��
    Object::WorldUpdate();



}
void Star::Render()
{
    Object::Render();
    Vector2 RenderVertex[5];
    for(int i = 0; i < 5; i++)
    {
        //L->W
        //���Ϳ� ����� �������� ���ִ� �Լ�
        D3DXVec2TransformCoord(
            &RenderVertex[i], &star[i], &W);
    }
    MoveToEx(g_MemDC, RenderVertex[0].x, RenderVertex[0].y, NULL);
    //�̵���ġ���� ������ġ�� ���߱�
    LineTo(g_MemDC, RenderVertex[2].x, RenderVertex[2].y);
    LineTo(g_MemDC, RenderVertex[4].x, RenderVertex[4].y);
    LineTo(g_MemDC, RenderVertex[1].x, RenderVertex[1].y);
    LineTo(g_MemDC, RenderVertex[3].x, RenderVertex[3].y);
    LineTo(g_MemDC, RenderVertex[0].x, RenderVertex[0].y);

}

