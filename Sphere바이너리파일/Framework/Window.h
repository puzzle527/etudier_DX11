#pragma once

//������� ��� �޸𸮿����� ����?
//Ŭ������ �ϳ���Ÿ���� �Ǹ鼭 ��Ÿ���� ������� ũ�⸸ŭ �Ҵ��ϴ� ��������ġ

//��ü�� staticȭ �ϸ� ������� static�� ���� �ʾƵ� ��
//�̱��� ����

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