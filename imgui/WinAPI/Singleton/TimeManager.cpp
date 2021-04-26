#include "stdafx.h"
#include "TimeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

TimeManager::TimeManager()
{
    //frequency ���ļ�

    /*��ǻ���� ���κ��忡�� �ϳ��� ���ػ� Ÿ�̸Ӱ� �����մϴ�.�� Ÿ�̸Ӵ� ��Ȯ�ϰ�
    ������ ���ļ�
    (��, 1�ʿ� �� Ÿ�̸��� ���ɿ� �´� ������)�� ���� ������ �����ϰ��� �ϴ� �ڵ����
    ���۰� ������
    CPU Ŭ������ ��� �� ���� ����ð��� ���� �� �ֽ��ϴ�.*/



    //QueryPerformanceFrequency���ػ� Ÿ�̸��� ���ļ�(1�ʴ� ������)�� �Ű������� ��� �Լ�
    //�������������� 0�� ��ȯ��
    //QueryPerformanceCounter:���ػ� Ÿ�̸��� ���� CPU�� Ŭ������ �Ű������� ��� �Լ�
    //�������������� 0�� ��ȯ��

    __int64 _periodFrequency;

    //�����Ǵ� ��ǻ�� ���
    if(QueryPerformanceFrequency(
        (LARGE_INTEGER*)(&_periodFrequency)))
    {
        _isHardware = true;
        QueryPerformanceCounter(
            (LARGE_INTEGER*)(&_lastTime));

        _timeScale = 1.0f / _periodFrequency;
    }
    //�������� �ʴ� ��ǻ�Ͷ��
    else
    {
        _isHardware = false;
        //timeGetTime:������(�ü��)�� ���۵Ǿ ���ݱ��� �帥 �ð��� 
        //1 / 1000 ��(milliseconds) ������ DWORD���� �����ϴ� �Լ���.
        _lastTime = timeGetTime();
        _timeScale = 0.001f;
    }
    //Ÿ�̸Ӱ� �����ɶ� 0������ ����ڴ�.
    _frameRate = 0;
    _FPSFrameCount = 0;
    _FPStimeElapsed = 0.0f;
    _worldTime = 0;

}

void TimeManager::SetFrame(UINT lock)
{
    //���� Ÿ�̸Ӹ� �����Ѵٸ�
    if(_isHardware)
    {
        //����ð���(Ŭ������) ���� �ʱ�ȭ ����
        QueryPerformanceCounter((LARGE_INTEGER*)(&_curTime));
    }
    else
    {
        //�������� ������ time�Լ��� �̿� �и�������(1/1000)
        _curTime = timeGetTime();
    }

    //�������ð��� ����ð��� �������Ӵ� �����(�ʴ���)
    _timeElapsed = (_curTime - _lastTime) * _timeScale;
    //                1000        500  *0.001

    //��� 1������ �̻� ������ ���ӿ� ���Ͽ�
    if(lock > 0)
    {
        //_timeElapsed �� 1.0f / lock���� �������� �ݺ�
        while(_timeElapsed < (1.0f / lock))
        {

            //���� Ÿ�̸Ӹ� �����Ѵٸ�
            if(_isHardware)
            {
                //����ð���(Ŭ������) ���� �ʱ�ȭ ����
                QueryPerformanceCounter((LARGE_INTEGER*)(&_curTime));
            }
            else
            {
                //�������� ������ time�Լ��� �̿� �и�������(1/1000)
                _curTime = timeGetTime();
                //1100
            }

            //�������ð��� ����ð��� �������Ӵ� �����(�ʴ���)
            _timeElapsed = (_curTime - _lastTime) * _timeScale;

        }
    }
    //������ �ð��� ���
    _lastTime = _curTime;

    _FPSFrameCount++;					//�ڵ����� ������ ī��Ʈ ����
    _FPStimeElapsed += _timeElapsed;	//�ʴ� ������ �ð� ����� ����
    _worldTime += _timeElapsed;			//��ü �ð� ����� ����

    if(_FPStimeElapsed > 1.0f)
    {
        _frameRate = _FPSFrameCount;
        _FPSFrameCount = 0;
        _FPStimeElapsed = 0.0f;
    }
}
