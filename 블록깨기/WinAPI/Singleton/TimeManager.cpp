#include "stdafx.h"
#include "TimeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

TimeManager::TimeManager()
{
    //frequency 주파수

    /*컴퓨터의 메인보드에는 하나의 고해상도 타이머가 존재합니다.이 타이머는 정확하고
    일정한 주파수
    (즉, 1초에 각 타이머의 성능에 맞는 진동수)를 갖기 때문에 측정하고자 하는 코드들의
    시작과 끝에서
    CPU 클럭수를 얻어 그 차로 수행시간을 얻을 수 있습니다.*/



    //QueryPerformanceFrequency고해상도 타이머의 주파수(1초당 진동수)를 매개변수가 얻는 함수
    //지원하지않으면 0을 반환함
    //QueryPerformanceCounter:고해상도 타이머의 현재 CPU의 클럭수를 매개변수가 얻는 함수
    //지원하지않으면 0을 반환함

    __int64 _periodFrequency;

    //지원되는 컴퓨터 라면
    if(QueryPerformanceFrequency(
        (LARGE_INTEGER*)(&_periodFrequency)))
    {
        _isHardware = true;
        QueryPerformanceCounter(
            (LARGE_INTEGER*)(&_lastTime));

        _timeScale = 1.0f / _periodFrequency;
    }
    //지원되지 않는 컴퓨터라면
    else
    {
        _isHardware = false;
        //timeGetTime:윈도우(운영체제)가 시작되어서 지금까지 흐른 시간을 
        //1 / 1000 초(milliseconds) 단위로 DWORD형을 리턴하는 함수다.
        _lastTime = timeGetTime();
        _timeScale = 0.001f;
    }
    //타이머가 생성될때 0값으로 만들겠다.
    _frameRate = 0;
    _FPSFrameCount = 0;
    _FPStimeElapsed = 0.0f;
    _worldTime = 0;

}

void TimeManager::SetFrame(UINT lock)
{
    //고성능 타이머를 지원한다면
    if(_isHardware)
    {
        //현재시간을(클럭단위) 먼저 초기화 해줌
        QueryPerformanceCounter((LARGE_INTEGER*)(&_curTime));
    }
    else
    {
        //지원하지 않으면 time함수를 이용 밀리세컨드(1/1000)
        _curTime = timeGetTime();
    }

    //마지막시간과 현재시간의 한프레임당 경과량(초단위)
    _timeElapsed = (_curTime - _lastTime) * _timeScale;
    //                1000        500  *0.001

    //적어도 1프레임 이상 나오는 게임에 한하여
    if(lock > 0)
    {
        //_timeElapsed 가 1.0f / lock보다 작을때만 반복
        while(_timeElapsed < (1.0f / lock))
        {

            //고성능 타이머를 지원한다면
            if(_isHardware)
            {
                //현재시간을(클럭단위) 먼저 초기화 해줌
                QueryPerformanceCounter((LARGE_INTEGER*)(&_curTime));
            }
            else
            {
                //지원하지 않으면 time함수를 이용 밀리세컨드(1/1000)
                _curTime = timeGetTime();
                //1100
            }

            //마지막시간과 현재시간의 한프레임당 경과량(초단위)
            _timeElapsed = (_curTime - _lastTime) * _timeScale;

        }
    }
    //마지막 시간을 기록
    _lastTime = _curTime;

    _FPSFrameCount++;					//자동으로 프레임 카운트 증가
    _FPStimeElapsed += _timeElapsed;	//초당 프레임 시간 경과량 증가
    _worldTime += _timeElapsed;			//전체 시간 경과량 증가

    if(_FPStimeElapsed > 1.0f)
    {
        _frameRate = _FPSFrameCount;
        _FPSFrameCount = 0;
        _FPStimeElapsed = 0.0f;
    }
}
