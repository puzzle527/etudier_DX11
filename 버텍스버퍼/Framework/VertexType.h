#pragma once

struct VertexP
{
    VertexP()
    {
    };
    VertexP(Vector3 pos)
    {
        position = pos;
    };
    Vector3 position;
};

struct VertexPC
{
    VertexPC()
    {
    };
    VertexPC(Vector3 pos, Color color)
    {
        this->position = pos;
        this->color = color;
    };
    Vector3 position;
    Color color;
};