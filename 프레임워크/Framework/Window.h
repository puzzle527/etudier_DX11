#pragma once
class Window
{
private:
	static Scene* main;
	static D3DDesc* d3dDesc;

public:
	static WPARAM Run(class Scene* main);
	static void SetDesc(D3DDesc* desc)
	{
		d3dDesc = desc;
	}
private:
	static void Create();
	static void Destroy();

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	static void MainLoop();
};