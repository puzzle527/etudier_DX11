#pragma once
class Star : public Object
{
public:
    Vector2 star[5];//원점이될위치포함
    void Init()override;
    void WorldUpdate()override;
    void Render()override;
};

