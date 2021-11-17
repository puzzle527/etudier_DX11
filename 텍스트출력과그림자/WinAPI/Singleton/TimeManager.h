#pragma once
//프로그램이 유지중일때
//고정프레임 발생이나 60
//혹은 시간값 계산을위해 하나만 존재
class TimeManager : public Singleton<TimeManager>
{

private:
    bool	_isHardware; //고성능 타이머를 지원하냐?

    __int64 _curTime;    //현재시간
    __int64 _lastTime;   //마지막시간

    float _FPStimeElapsed; //FPS 마지막시간과 현재 시간의 경과량
    float _timeScale;      //시간 단위 
    DWORD _FPSFrameCount;  //FPS 카운트


    DWORD _frameRate;      //FPS
    float _timeElapsed;    //프레임당 경과시간
    float _worldTime;      //전체 시간 경과량

public:
    TimeManager();
    ~TimeManager() {};

    //초기화 하지 않으면 프레임은 60프레임으로 고정
    void SetFrame(UINT lock = 60);

    //한 프레임 경과시간 가져오기 1/60
    float GetElapsedTime() { return _timeElapsed; }
    //전체 시간 경과량 가져오기
    float GetWorldTime() { return _worldTime; }
    //현재 FPS 가져오기
    unsigned long GetFrameRate() { return _frameRate; }

};

