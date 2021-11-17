#include "stdafx.h"
#include "Main.h"

Main::Main()
{
}

Main::~Main()
{
}

void Main::Init()
{
}


void Main::Update()
{
}


void Main::Render()
{
}

void Main::ResizeScreen()
{
}


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	D3DDesc desc;
	desc.AppName = L"Game1";
	desc.Instance = instance;
	desc.bFullScreen = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;
	Window::SetDesc(&desc);

	Main* main = new Main();
	WPARAM wParam = Window::Run(main);
	delete main;

	return wParam;
}