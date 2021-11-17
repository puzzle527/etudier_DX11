#pragma once
//��Ÿ�����δ� ��ü������� ����.
class Scene
{
public:
	virtual ~Scene() {};
	//���� �س��� �Լ�
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ResizeScreen() = 0;
};
