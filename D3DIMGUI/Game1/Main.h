#pragma once
class Main : public Scene
{
private:
	GameObject* Root;


public:
	Main();//����
	~Main();//�Ҹ�
	virtual void Init() override; //�ʱ�ȭ

	//Loop (Tick)
	virtual void Update() override;//����
	virtual void Render() override;//���
	virtual void ResizeScreen() override;//����������

};

