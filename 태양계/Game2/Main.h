#pragma once
class Main : public Scene
{
public:
	Main();//����
	~Main();//�Ҹ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void ImGuiRender() override;//���
	virtual void ResizeScreen() override;

};