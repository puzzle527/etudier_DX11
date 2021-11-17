#pragma once
class Main : public Scene
{
private:
	Actor* Ob1;
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

