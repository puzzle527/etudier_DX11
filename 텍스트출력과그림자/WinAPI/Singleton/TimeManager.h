#pragma once
//���α׷��� �������϶�
//���������� �߻��̳� 60
//Ȥ�� �ð��� ��������� �ϳ��� ����
class TimeManager : public Singleton<TimeManager>
{

private:
    bool	_isHardware; //���� Ÿ�̸Ӹ� �����ϳ�?

    __int64 _curTime;    //����ð�
    __int64 _lastTime;   //�������ð�

    float _FPStimeElapsed; //FPS �������ð��� ���� �ð��� �����
    float _timeScale;      //�ð� ���� 
    DWORD _FPSFrameCount;  //FPS ī��Ʈ


    DWORD _frameRate;      //FPS
    float _timeElapsed;    //�����Ӵ� ����ð�
    float _worldTime;      //��ü �ð� �����

public:
    TimeManager();
    ~TimeManager() {};

    //�ʱ�ȭ ���� ������ �������� 60���������� ����
    void SetFrame(UINT lock = 60);

    //�� ������ ����ð� �������� 1/60
    float GetElapsedTime() { return _timeElapsed; }
    //��ü �ð� ����� ��������
    float GetWorldTime() { return _worldTime; }
    //���� FPS ��������
    unsigned long GetFrameRate() { return _frameRate; }

};

