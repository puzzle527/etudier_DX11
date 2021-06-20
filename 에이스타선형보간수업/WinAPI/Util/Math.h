#pragma once
#include "stdafx.h"

struct Int2
{
    int x;
    int y;
    //�⺻ ������
    Int2()
    {
        x = 0;
        y = 0;
    }
    Int2(int x,int y)
    {
        //this�� ������ ����Ű�� ������
        this->x = x;
        this->y = y;
    }
    //������ ����,������
    //         *this == dest
    bool operator == (Int2 dest)
    {
        return (x == dest.x && y == dest.y);
    }

};



template <typename T>
static void MySwap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
};

template <typename T>
void MyShuffle(T* arr, int range, int max)
{
    for(int i = 0; i < max; i++)
    {
        int dest = rand() % range;
        int sour = rand() % range;
        MySwap(arr[dest], arr[sour]);
    }
};
// start ���� end���� ����
// 100 ~ 200
// rand() % 101 - 0 ~ 100
// rand() % 101 + 100 - 100 ~ 200
static int RndInt(int start = 0, int end = 1)
{
    return rand() % (end - start + 1) + start;
};
//                          2.5                4.5   
static float RndFloat(float start = 0.0f, float end = 1.0f)
{
    return (float)rand() / (float)RAND_MAX * (end - start) + start;
};

//�ּ� �ִ밪 ���ϱ�
template <typename T>// 700   0         600      
static T Saturate(T& in, T min = 0, T max = 1)
{
    if(in < min)
    {
        in = min;
        return min;
    }
    else if(in > max)
    {
        in = max;
        return max;
    }
    return in;
}





 static float DirToRadian(Vector2 Dir)
 {
     //���� �������Ͱ� �ƴҼ��������ϱ�
     D3DXVec2Normalize(&Dir, &Dir);
     float Seta;
     if(Dir.y < 0)
     {
         //          360.0*TORADIAN
         Seta = 2.0f*PI - acosf(Dir.x);
     }
     else
     {
         Seta = acosf(Dir.x);
     }
     return Seta;
 }
 // ���� ����
 static float ReverseSeta(float& in, bool isYAxis = true)
 {
     //���Ϲ���
     if (isYAxis)
     {
         in = 2.0f * PI - in;
         return in;
     }
     else
     {
         in = PI - in;
         return in;
     }

 }

 static Vector2 Lerp(Vector2 from, Vector2 to, float g)
 {
     return from + (to - from) * g;
 }