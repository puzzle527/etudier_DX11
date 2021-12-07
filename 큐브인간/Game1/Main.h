#pragma once

enum StateEnum
{
	IDLE,
	WALK
};


class Main : public Scene
{
private:
	Actor* Ob1;
	Actor* Ob2;
	Actor* Grid;//����ٰ� ����� ������Ʈ�� �ҷ��ð�
	StateEnum state = IDLE;
	float StateDuration = 0.0f;
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

