#pragma once
class Main : public Scene
{
public:
	Main();//생성
	~Main();//소멸
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void ImGuiRender() override;//출력
	virtual void ResizeScreen() override;

};