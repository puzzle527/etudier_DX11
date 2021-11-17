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
	Root = new GameObject();
	Root->name = "Root";

	Root->child["Hip"] = new GameObject();
	Root->child["Hip"]->name = "Hip";

	Root->child["Head"] = new GameObject();
	Root->child["Head"]->name = "Head";
}


void Main::Update()
{
	//ImGui::Text("Hello");
}


void Main::Render()
{
	Root->ImGuiRender();
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
	desc.Background = Color(0.7f, 0.7f, 0.7f, 1);
	D3d::SetDesc(desc);

	//추상화(인터페이스) = 하위클래스
	Scene* main = new Main();
	WPARAM wParam = Window::Run(main);
	delete main;

	return wParam;

	Vector2 WorldSize;
	//XMFLOAT2 a;
	//XMVECTOR b;

	/*WorldSize.x; WorldSize.y;
	b.m128_f32; b.m128_i16;
	a.x; a.y;*/


	//return wParam;
}