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

	Grid = Actor::Create("Grid");
}


void Main::Update()
{
	Ob1->Update();
	Grid->Update();
	Cam1->Update();

	//카메라 이동
	if (KEYBOARD->KeyPress('W'))
	{
		Cam1->position += Cam1->Forward()*0.01f;
	}
	if (KEYBOARD->KeyPress('S'))
	{
		Cam1->position += -Cam1->Forward() * 0.01f;
	}
	if (KEYBOARD->KeyPress('A'))
	{
		Cam1->position += -Cam1->Right() * 0.01f;
	}
	if (KEYBOARD->KeyPress('D'))
	{
		Cam1->position += Cam1->Right() * 0.01f;
	}
	if (KEYBOARD->KeyPress('Q'))
	{
		Cam1->position += -Cam1->Up() * 0.01f;
	}
	if (KEYBOARD->KeyPress('E'))
	{
		Cam1->position += Cam1->Up() * 0.01f;
	}
	POINT mouse;
	if (GetCursorPos(&mouse))
	{
		ImGui::Text("Mouse X: %d Y: %d",mouse.x, mouse.y);
	}

	//마우스 우클릭시 최초1회
	if (KEYBOARD->KeyDown(VK_RBUTTON))
	{

	}
	//마우스 우클릭시
	if (KEYBOARD->KeyPress(VK_RBUTTON))
	{

	}
	//마우스 우클릭하고 뗄때 1회
	if (KEYBOARD->KeyUp(VK_RBUTTON))
	{

	}





	//카메라 마우스로 회전


	/*if (KEYBOARD->KeyPress(VK_LEFT))
	{
		Ob1->position.x -= 1.0f;
	}
	if (KEYBOARD->KeyPress('A'))
	{
		Ob1->position.x -= 1.0f;
	}
	if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		Ob1->position.x += 1.0f;
	}
	if (KEYBOARD->KeyPress('D'))
	{
		Ob1->position.x += 1.0f;
	}*/
}


void Main::Render()
{
	Cam1->Set();
	Ob1->Render();
	Grid->Render();

	//충돌했으면
	/*Vector3 v3 = Ob1->position - Ob2->position;
	float sca = v3.Length();
	if (sca < 20)
	{
		ImGui::Text("collision");
	}*/

}
void Main::ImGuiRender()
{

	ImGui::Begin("Hierarchy");
	Ob1->ImGuiRender();
	Grid->ImGuiRender();
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