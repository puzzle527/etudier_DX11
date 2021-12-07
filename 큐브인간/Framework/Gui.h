#pragma once


class Gui :public Singleton<Gui>
{
public:
	
	static int ID;
	static LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void Update();
	void Render();
	static void IDSet();

	Gui();
	~Gui();
private:
	void ApplyStyle();
};