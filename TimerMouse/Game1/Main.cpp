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
	ImGui::Text("WorldTime: %d", TIMER->GetWorldTime());
	ImGui::Text("FPS: %d", TIMER->GetFPS());
	ImGui::Text("Delta: %f", DELTA);


	Ob1->Update();
	Grid->Update();
	Cam1->Update();

	//카메라 이동
	if (KEYBOARD->KeyPress('W'))
	{
		//                                  초당100움직임 xyz/s
		Cam1->position += Cam1->Forward() * DELTA * 100.0f;
	}
	if (KEYBOARD->KeyPress('S'))
	{
		Cam1->position += -Cam1->Forward() * DELTA * 100.0f;
	}
	if (KEYBOARD->KeyPress('A'))
	{
		Cam1->position += -Cam1->Right() * DELTA * 100.0f;
	}
	if (KEYBOARD->KeyPress('D'))
	{
		Cam1->position += Cam1->Right() * DELTA * 100.0f;
	}
	if (KEYBOARD->KeyPress('Q'))
	{
		Cam1->position += -Cam1->Up() * DELTA * 100.0f;
	}
	if (KEYBOARD->KeyPress('E'))
	{
		Cam1->position += Cam1->Up() * DELTA * 100.0f;
	}

	//마우스 우클릭시
	if (MOUSE->Press(RBUTTON))
	{
		Vector3 Rot;
		Rot.x = MOUSE->movePosition.y * 0.001f;
		Rot.y = MOUSE->movePosition.x * 0.001f;
		Cam1->rotation += Rot;
	}
	Cam1->position += Cam1->Forward() * MOUSE->wheelMoveValue.z;



	//과제

	//큐브를 1초간 30도씩 x축으로 회전하는
	if (KEYBOARD->KeyPress('1'))
	{

	}
	//큐브를 1초간 1000도씩 x축으로 회전하는
	if (KEYBOARD->KeyPress('2'))
	{

	}
	//큐브를 1초간 Forwad방향으로 100이동하는
	if (KEYBOARD->KeyPress('3'))
	{

	}
	//큐브를 1초간 Forwad방향으로  100가속도로 100초기속도 이동하는
	if (KEYBOARD->KeyPress('4'))
	{

	}



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
	desc.bVsync = true;
	D3d::SetDesc(desc);

	//추상화(인터페이스) = 하위클래스
	Scene* main = new Main();
	WPARAM wParam = Window::Run(main);
	delete main;

	return wParam;
}