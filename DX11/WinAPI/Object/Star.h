#pragma once
class Star : public Object
{
public:
    Vector2 star[5];//�����̵���ġ����
    void Init()override;
    void WorldUpdate()override;
    void Render()override;
};

