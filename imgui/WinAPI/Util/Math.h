#pragma once
#include "stdafx.h"

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
// start 에서 end까지 난수
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

//최소 최대값 정하기
template <typename T>// 700   0         600      
static T Saturate(T in, T min = 0, T max = 1)
{
    if(in < min)
    {
        return min;
    }
    else if(in > max)
    {
        return max;
    }
    return in;
}





 static float DirToRadian(Vector2 Dir)
 {
     //만약 단위벡터가 아닐수도있으니까
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

