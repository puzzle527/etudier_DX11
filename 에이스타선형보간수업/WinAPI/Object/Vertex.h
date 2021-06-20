#pragma once
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