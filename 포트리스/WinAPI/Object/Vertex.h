#pragma once
#include "stdafx.h"

//정점단위로 도형을이루면
//이동,확대 축소,회전표현이 가능하다
namespace Vertex
{

    //정점 구조체
    //3축회전 사용하기위해 Vector3사용
    struct VertexP
    {
        VertexP() { Position.z = 0.0f; }

        VertexP(Vector3 position)
            : Position(position) //이니셜라이저
        {
            Position.z = 0.0f;
        }

        Vector3 Position;
    };

    struct VertexPC
    {
        VertexPC() { Position.z = 0.0f; }

        VertexPC(Vector3 position, Color  color)
            : Position(position), color(color)
        {
            Position.z = 0.0f;
        }

        Vector3 Position;
        Color   color;
    };

    struct VertexPT
    {
        VertexPT() { Position.z = 0.0f; }

        VertexPT(Vector3 position, Vector2  uv)
            : Position(position), Uv(uv)
        {
            Position.z = 0.0f;
        }

        Vector3 Position;
        //텍스쳐 좌표 (0~1)
        Vector2 Uv; 
    };
}