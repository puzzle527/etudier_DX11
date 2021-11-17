#pragma once
class Main : public Scene
{
public:
	Main();//»ý¼º
	~Main();//¼Ò¸ê
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

};

