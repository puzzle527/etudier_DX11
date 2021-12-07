#pragma once
class Keyboard : public Singleton<Keyboard>
{
private:
    //배열크기를 키값만큼 갖는다
    byte keyState[256];//현재상태
    byte keyOldState[256];//저번업데이트상태
    byte keyMap[256];

    //키입력에서만 접근가능한  익명 enum
    enum
    {
        KEY_INPUT_STATUS_DOWN,
        KEY_INPUT_STATUS_PRESS,
        KEY_INPUT_STATUS_NONE,
        KEY_INPUT_STATUS_UP,
    };
public:
    Keyboard();
    ~Keyboard();

    bool KeyDown(int KeyCode); //눌렀을때 최초1회
    bool KeyPress(int KeyCode);//누르고있을때
    bool KeyUp(int KeyCode); //눌렀다가 떼었을때 최초1회
    void Update();

};



