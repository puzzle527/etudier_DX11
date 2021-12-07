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
	Actor* Grid;//여기다가 저장된 오브젝트를 불러올것
	StateEnum state = IDLE;
	float StateDuration = 0.0f;
	Camera* Cam1;


public:
	Main();//생성
	~Main();//소멸
	virtual void Init() override; //초기화

	//Loop (Tick)
	virtual void Update() override;//갱신
	virtual void Render() override;//출력
	virtual void ImGuiRender() override;//출력
	virtual void ResizeScreen() override;//사이즈조절

};

