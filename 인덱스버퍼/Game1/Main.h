#pragma once
class Main : public Scene
{
private:
	Actor* Ob1;
	Camera* Cam1;


public:
	Main();//����
	~Main();//�Ҹ�
	virtual void Init() override; //�ʱ�ȭ

	//Loop (Tick)
	virtual void Update() override;//����
	virtual void Render() override;//���
	virtual void ImGuiRender() override;//���
	virtual void ResizeScreen() override;//����������

};

