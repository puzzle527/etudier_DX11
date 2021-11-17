#include "Framework.h"
#include "Window.h"
Scene* Window::main = NULL;
D3DDesc* Window::d3dDesc = NULL;

WPARAM Window::Run(Scene* main)
{
	Window::main = main;
	Create();
	main->Init();
	MSG msg = { 0 };
	while (true)

	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainLoop();
		}
	}

	Destroy();

	return msg.wParam;
}

void Window::Create()
{

	WNDCLASSEXW wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = d3dDesc->Instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = d3dDesc->AppName.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEXW);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	if (d3dDesc->bFullScreen == true)
	{
		DEVMODE devMode = { 0 };
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPelsWidth = (DWORD)d3dDesc->Width;
		devMode.dmPelsHeight = (DWORD)d3dDesc->Height;
		devMode.dmBitsPerPel = 32;
		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	}

	d3dDesc->Handle = CreateWindowExW
	(
		WS_EX_APPWINDOW
		, d3dDesc->AppName.c_str()
		, d3dDesc->AppName.c_str()
		, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, NULL
		, (HMENU)NULL
		, d3dDesc->Instance
		, NULL
	);
	assert(d3dDesc->Handle != NULL);


	RECT rect = { 0, 0, (LONG)d3dDesc->Width, (LONG)d3dDesc->Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)d3dDesc->Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)d3dDesc->Height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow
	(
		d3dDesc->Handle
		, centerX, centerY
		, rect.right - rect.left, rect.bottom - rect.top
		, TRUE
	);
	ShowWindow(d3dDesc->Handle, SW_SHOWNORMAL);
	SetForegroundWindow(d3dDesc->Handle);
	SetFocus(d3dDesc->Handle);

	ShowCursor(true);
}

void Window::Destroy()
{
	if (d3dDesc->bFullScreen == true)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(d3dDesc->Handle);

	UnregisterClass(d3dDesc->AppName.c_str(), d3dDesc->Instance);
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_SIZE)
	{
		if (main != NULL)
		{
			d3dDesc->Width = (float)LOWORD(lParam);
			d3dDesc->Height = (float)HIWORD(lParam);

			main->ResizeScreen();
		}
	}

	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

void Window::MainLoop()
{
	main->Update();
	main->Render();
}
