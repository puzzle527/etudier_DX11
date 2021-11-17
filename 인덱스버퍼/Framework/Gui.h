#pragma once


class Gui :public Singleton<Gui>
{
public:

	static LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void Update();
	void Render();

	Gui();
	~Gui();
private:
	void ApplyStyle();
};