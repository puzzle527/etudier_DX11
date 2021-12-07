#pragma once

enum class VertexType
{
    V_P,
    V_PC,
};

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
    static D3D11_INPUT_ELEMENT_DESC LayoutDesc[];
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
    static D3D11_INPUT_ELEMENT_DESC LayoutDesc[];
};

