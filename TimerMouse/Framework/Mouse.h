#pragma once
#define MAX_INPUT_MOUSE 8
#define LBUTTON 0
#define RBUTTON 1
#define MBUTTON 2

class Mouse : public Singleton<Mouse>
{
public:
	Mouse();
	~Mouse();
	void Update();
	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);


	bool Down(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_DOWN;
	}

	bool Up(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_UP;
	}

	bool Press(DWORD button)
	{
		return buttonMap[button] <= BUTTON_INPUT_STATUS_PRESS;
	}


public:
	Vector3 position; //마우스 위치
	Vector3 movePosition; //마우스 이동벡터
	Vector3 wheelMoveValue;

private:



	HWND handle;


	byte buttonStatus[MAX_INPUT_MOUSE];
	byte buttonOldStatus[MAX_INPUT_MOUSE];
	byte buttonMap[MAX_INPUT_MOUSE];

	Vector3 wheelStatus;
	Vector3 wheelOldStatus;
	Vector3 oldPostion;
	Vector3 currentPostion;

	DWORD timeDblClk;
	DWORD startDblClk[MAX_INPUT_MOUSE];
	int buttonCount[MAX_INPUT_MOUSE];

	enum
	{
		BUTTON_INPUT_STATUS_DOWN = 0,
		BUTTON_INPUT_STATUS_PRESS,
		BUTTON_INPUT_STATUS_NONE,
		BUTTON_INPUT_STATUS_UP,
		BUTTON_INPUT_STATUS_DBLCLK
	};
};