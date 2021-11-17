#pragma once
using namespace FMOD;
#define EXTRACHANNERBUFFER 5
#define SOUNDBUFFER 20
#define TOTALSOUNDBUFFER SOUNDBUFFER * EXTRACHANNERBUFFER


class SoundManager : public Singleton<SoundManager>
{
private:
    Sound** sound;
    Channel** channel;
    System* system;

    map<string, Sound*>     SoundMap;
    map<string, Channel*>   ChannelMap;

public:
    SoundManager();
    ~SoundManager();
    bool AddSound(string File, string Key,
        bool loop = false);//반복재생?
    void Play(string Key);
    void Stop(string Key);
    //일시정지
    void Pause(string Key);
    //일시정지 해제
    void Resume(string Key);   //    0 ~ 1
    void SetVolume(string Key, float scale = 1.0f);
    void Update(); //내부적으로 갱신값이 필요하여 호출

};

