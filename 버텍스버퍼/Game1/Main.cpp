#include "stdafx.h"
#include "Main.h"

//디버깅


Main::Main()
{
}

Main::~Main()
{
	SafeRelease(Ob1);
}

void Main::Init()
{
	Ob1 = Actor::Create("Root");
	Ob1->AddChild(GameObject::Create("Hip"));

	Ob1->FindObject("Hip")->AddChild(GameObject::Create("Head"));
	Ob1->FindObject("Root")->AddChild(GameObject::Create("Head2"));

	Ob1->position.x = 3;
}


void Main::Update()
{
	/*ImGui::Begin("Hello, world!");
	ImGui::ColorEdit3("clear color", (float*)&D3D->GetDesc().Background);
	ImGui::End();*/
}


void Main::Render()
{
	Ob1->Render();



	ImGui::Begin("Hierarchy");
	Ob1->ImGuiRender();
	ImGui::End();
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
}