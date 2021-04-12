#pragma once
#define MAX_INPUT_KEY 255
//                  ��ӹ����鼭<T>�� ����
class KeyManager : public Singleton<KeyManager>
{
    /*static KeyManager* Instance;*/
private:
    //�迭ũ�⸦ Ű����ŭ ���´�
    byte keyState[MAX_INPUT_KEY];//�������
    byte keyOldState[MAX_INPUT_KEY];//����������Ʈ����
    byte keyMap[MAX_INPUT_KEY];

    //Ű�Է¿����� ���ٰ�����  �͸� enum
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

    bool KeyDown(int KeyCode); //�������� ����1ȸ
    bool KeyPress(int KeyCode);//������������
    bool KeyUp(int KeyCode); //�����ٰ� �������� ����1ȸ
    void Update();

};

