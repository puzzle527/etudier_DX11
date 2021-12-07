#pragma once

//멤버변수 어느 메모리영역에 존재?
//클래스가 하나의타입이 되면서 그타입의 멤버변수 크기만큼 할당하는 공간에배치

//객체를 static화 하면 모든멤버를 static을 쓰지 않아도 됨
//싱글턴 패턴

class Window
{
private:
	static Scene* main;

public:
	static WPARAM Run(class Scene* main);
private:
	static void Create();
	static void Destroy();

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	static void MainLoop();
};