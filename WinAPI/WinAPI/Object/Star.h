#pragma once
class Star : public Object
{
	UINT                Slice;

	ID3D11Buffer*		VertexBuffer;
	UINT				VertexCount;//Á¤Á¡°¹¼ö
	VertexPC*           Vertex;
public:
	Star(UINT Slice = 5, Vector2 pivot = Vector2(0.0f, 0.0f));
	~Star();
    void Init()override;
    void WorldUpdate()override;
    void Render()override;
};

