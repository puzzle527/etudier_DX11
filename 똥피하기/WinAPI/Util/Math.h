#pragma once
#include "stdafx.h"

struct Int2
{
    int x;
    int y;
    Int2() {}
    Int2(int x, int y)
    {
        //this 본인을가르키는 포인터
        this->x = x;
        this->y = y;
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



//start~end 까지 난수발생
//st    en
//100 ~ 300
//rand()%(300 -100 + 1) + 100
static int RndInt(int start = 0, int end = 1)
{
    return rand() % (end - start + 1) + start;
};

static float RndFloat(float start = 0.0f, float end = 1.0f)
{
    return (float)rand() / (float)RAND_MAX * (end - start) + start;
};

//최소 최대값 정하기
template <typename T>  
static T Saturate(T in, T min = 0, T max = 1)
{
    //-1     0
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


//static은 헤더여러번포함되어있어서 중복정의 방지
static float DirToRadian(Vector2 Dir)
{
    //단위벡터가 아닌것도 읽어오게
    D3DXVec2Normalize(&Dir,&Dir);
    float Seta;
    if(Dir.y < 0)
    {
        Seta = 2.0f * PI - acosf(Dir.x);
    }
    else
    {
        Seta = acosf(Dir.x);
    }
    return Seta;
}