#include "Framework.h"
#include "VertexType.h"
D3D11_INPUT_ELEMENT_DESC VertexP::LayoutDesc[] =
{
    { "POSITION",
    0,
    DXGI_FORMAT_R32G32B32_FLOAT,
    0,
    0,
    D3D11_INPUT_PER_VERTEX_DATA,
    0 }
};
D3D11_INPUT_ELEMENT_DESC VertexPC::LayoutDesc[] =
{
    { "POSITION",
    0,
    DXGI_FORMAT_R32G32B32_FLOAT,
    0,
    0,
    D3D11_INPUT_PER_VERTEX_DATA,
    0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
    12,
    D3D11_INPUT_PER_VERTEX_DATA, 0 },
};