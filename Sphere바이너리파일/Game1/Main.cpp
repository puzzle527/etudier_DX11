#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	
}

Main::~Main()
{
	SafeRelease(Ob1);
	SafeRelease(Cam1);
}

void Main::Init()
{
	Cam1 = Camera::Create("Cam1");
	Ob1 = Actor::Create("Root");
	Ob1->position = Vector3(0, 0, 50);
	Ob1->scale = Vector3(10, 10, 10);

	Ob2 = Actor::Create("Root2");
	Ob2->position = Vector3(20, 0, 50);
	Ob2->scale = Vector3(10, 10, 10);
}


void Main::Update()
{
	Ob1->Update();
	Ob2->Update();
	Cam1->Update();
}


void Main::Render()
{
	Cam1->Set();
	Ob1->Render();
	Ob2->Render();

	//충돌했으면
	Vector3 v3 = Ob1->position - Ob2->position;
	float sca = v3.Length();
	if (sca < 20)
	{
		ImGui::Text("collision");
	}

}
void Main::ImGuiRender()
{

	ImGui::Begin("Hierarchy");
	Ob1->ImGuiRender();
	Ob2->ImGuiRender();
	Cam1->ImGuiRender();
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