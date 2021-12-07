#include "Framework.h"
#include "Timer.h"

Timer::Timer()
{
    //현재 시간 측정
    LastTime = chrono::steady_clock::now();
    //타이머 생성시엔 경과시간을 알수없다.
    deltaTime = 0.0f;
    //처음 실행시간은 0
    WorldTime = 0.0f;
    FPS = 0;
    FPSCount = 0;
    FPSTimeElapsed = 0.0f;
}

void Timer::Chronometry()
{
    CurrentTime = chrono::steady_clock::now();
    //지난시간 - 현재시간값을 나노 초단위로 받기
    chrono::duration<double> Delta =
        CurrentTime - LastTime;
    //        초단위로 변경하여 값받기
    deltaTime = (float)Delta.count();

    //마지막 시간을 기록
    LastTime = CurrentTime;
    //전체 시간 경과량을 연산
    WorldTime += deltaTime;

    FPSTimeElapsed += deltaTime;

    FPSCount++;
    //FPSTimeElapsed 이 1초가 넘었을때
    if (FPSTimeElapsed > 1.0f)
    {
        FPS = FPSCount;
        FPSCount = 0;
        FPSTimeElapsed = 0.0f;
    }
}
