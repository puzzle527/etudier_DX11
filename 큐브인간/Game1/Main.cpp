#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	
}

Main::~Main()
{
	Cam1->SaveFile("Cam");
	SafeRelease(Cam1);
	Ob1->SaveFile("Sun");
	Ob2->SaveFile("CubeMan");
	SafeRelease(Ob1);
	SafeRelease(Ob2);
	Grid->SaveFile("Grid");
	SafeRelease(Grid);
	
}

void Main::Init()
{
	Cam1 = RESOURCE->LoadCam("Cam");
	Ob1 = RESOURCE->LoadActor("Sun");
	Ob2 = RESOURCE->LoadActor("CubeMan");
	Grid = RESOURCE->LoadActor("Grid");
}


void Main::Update()
{
	ImGui::Text("WorldTime: %f", TIMER->GetWorldTime());
	ImGui::Text("FPS: %d", TIMER->GetFPS());
	ImGui::Text("Delta: %f", DELTA);

	Ob1->Update();
	Ob2->Update();
	Grid->Update();
	Cam1->Update();

	////지구의 자전
	//Ob1->FindObject("Earth")->rotation.y += ToRadian(DELTA * -60.0f);
	////지구의 공전
	//Ob1->FindObject("EarthBone")->rotation.y += ToRadian(DELTA * 60.0f);


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
	//휠키로 카메라 앞뒤조절
	Cam1->position += Cam1->Forward() * MOUSE->wheelMoveValue.z;

	StateDuration += DELTA;
	static float mul = 1.0f;
	if (state == IDLE)
	{
		if (StateDuration > 1.0f)
		{
			StateDuration -= 1.0f;
			mul *= -1.0f;
		}

		Ob2->FindObject("Neck")->rotation.y += DELTA * mul;
		//IDLE -> WALK
		if (KEYBOARD->KeyDown(VK_UP) || KEYBOARD->KeyPress(VK_DOWN))
		{
			Ob2->FindObject("Neck")->rotation.y = 0;
			state = WALK;
			StateDuration = 0.0f;
		}
	}
	else if (state == WALK)
	{
		if (StateDuration > 1.0f)
		{
			StateDuration -= 1.0f;
			mul *= -1.0f;
		}

		if (KEYBOARD->KeyPress(VK_UP))
		{
			Ob2->position += Ob2->Forward() * 50.0f * DELTA;
			Ob2->FindObject("Rsholder")->rotation.x += DELTA * mul;
			Ob2->FindObject("RLegJoint")->rotation.x -= DELTA * mul;
		}
		else if (KEYBOARD->KeyPress(VK_DOWN))
		{
			Ob2->position -= Ob2->Forward() * 50.0f * DELTA;
		}

		//WALK -> IDLE 
		if (KEYBOARD->KeyUp(VK_UP)|| KEYBOARD->KeyUp(VK_DOWN))
		{
			state = IDLE;
			StateDuration = 0.0f;
		}
	}

	
	//좌우회전
	if (KEYBOARD->KeyPress(VK_LEFT))
	{
		Ob2->rotation.y -= ToRadian(100.0f * DELTA);
	}
	else if (KEYBOARD->KeyPress(VK_RIGHT))
	{
		Ob2->rotation.y += ToRadian(100.0f * DELTA);
	}

}

//태양계 구현하기



void Main::Render()
{
	Cam1->Set();
	Ob1->Render();
	Ob2->Render();
	Grid->Render();
}
void Main::ImGuiRender()
{

	ImGui::Begin("Hierarchy");
	Ob1->ImGuiRender();
	Ob2->ImGuiRender();
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

	return (int)wParam;
}