#pragma once
#define MAX_INPUT_KEY 255
//                  상속받으면서<T>를 정의
class KeyManager : public Singleton<KeyManager>
{
    /*static KeyManager* Instance;*/
private:
    //배열크기를 키값만큼 갖는다
    byte keyState[MAX_INPUT_KEY];//현재상태
    byte keyOldState[MAX_INPUT_KEY];//저번업데이트상태
    byte keyMap[MAX_INPUT_KEY];

    //키입력에서만 접근가능한  익명 enum
    enum
    {
        KEY_INPUT_STATUS_NONE = 0,
        KEY_INPUT_STATUS_DOWN,
        KEY_INPUT_STATUS_UP,
        KEY_INPUT_STATUS_PRESS,
    };
public:
    KeyManager();
    ~KeyManager();

    bool KeyDown(int KeyCode); //눌렀을때 최초1회
    bool KeyPress(int KeyCode);//누르고있을때
    bool KeyUp(int KeyCode); //눌렀다가 떼었을때 최초1회
    void Update();

};

