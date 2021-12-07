#include "Framework.h"
#include "Timer.h"

Timer::Timer()
{
    //���� �ð� ����
    LastTime = chrono::steady_clock::now();
    //Ÿ�̸� �����ÿ� ����ð��� �˼�����.
    deltaTime = 0.0f;
    //ó�� ����ð��� 0
    WorldTime = 0.0f;
    FPS = 0;
    FPSCount = 0;
    FPSTimeElapsed = 0.0f;
}

void Timer::Chronometry()
{
    CurrentTime = chrono::steady_clock::now();
    //�����ð� - ����ð����� ���� �ʴ����� �ޱ�
    chrono::duration<double> Delta =
        CurrentTime - LastTime;
    //        �ʴ����� �����Ͽ� ���ޱ�
    deltaTime = (float)Delta.count();

    //������ �ð��� ���
    LastTime = CurrentTime;
    //��ü �ð� ������� ����
    WorldTime += deltaTime;

    FPSTimeElapsed += deltaTime;

    FPSCount++;
    //FPSTimeElapsed �� 1�ʰ� �Ѿ�����
    if (FPSTimeElapsed > 1.0f)
    {
        FPS = FPSCount;
        FPSCount = 0;
        FPSTimeElapsed = 0.0f;
    }
}
