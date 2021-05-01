#include "stdafx.h"
#include "KeyManager.h"

KeyManager::KeyManager()
{
    ZeroMemory(keyState, sizeof(keyState));
    ZeroMemory(keyOldState, sizeof(keyOldState));
    ZeroMemory(keyMap, sizeof(keyMap));
}

KeyManager::~KeyManager()
{
}

bool KeyManager::KeyDown(int KeyCode)
{
    return keyMap[KeyCode] == KEY_INPUT_STATUS_DOWN;
}

bool KeyManager::KeyPress(int KeyCode)
{
    return keyMap[KeyCode] == KEY_INPUT_STATUS_PRESS;
}

bool KeyManager::KeyUp(int KeyCode)
{
    return keyMap[KeyCode] == KEY_INPUT_STATUS_UP;
}

void KeyManager::Update()
{
    //�޸𸮺��� keyOldState = keyState 
    memcpy(keyOldState, keyState, sizeof(keyOldState));

    //������ �迭�� �ʱ�ȭ
    ZeroMemory(keyState, sizeof(keyState));
    ZeroMemory(keyMap, sizeof(keyMap));


    //���� ȣ����¿����� Ű�Է°��� �������� �Լ�
    GetKeyboardState(keyState);
    // 0x80
    // 0x81
    // 0x00
    // 0x01

    for(DWORD i = 0; i < MAX_INPUT_KEY; i++)
    {
        byte key = keyState[i] & 0x80;
        //���׿�����   (bool)? 1{} 0{}
        keyState[i] = key ? 1 : 0;

        /*if(key)
            keyState[i] = 1;
        else
            keyState[i] = 0;*/

        int oldState = keyOldState[i];
        int state = keyState[i];

        if(oldState == 0 && state == 1)
            keyMap[i] = KEY_INPUT_STATUS_DOWN; //���� 0, ���� 1 - KeyDown
        else if(oldState == 1 && state == 0)
            keyMap[i] = KEY_INPUT_STATUS_UP; //���� 1, ���� 0 - KeyUp
        else if(oldState == 1 && state == 1)
            keyMap[i] = KEY_INPUT_STATUS_PRESS; //���� 1, ���� 1 - KeyPress
        else
            keyMap[i] = KEY_INPUT_STATUS_NONE;
    }

}
