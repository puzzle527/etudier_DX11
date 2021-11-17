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
        bool loop = false);//�ݺ����?
    void Play(string Key);
    void Stop(string Key);
    //�Ͻ�����
    void Pause(string Key);
    //�Ͻ����� ����
    void Resume(string Key);   //    0 ~ 1
    void SetVolume(string Key, float scale = 1.0f);
    void Update(); //���������� ���Ű��� �ʿ��Ͽ� ȣ��

};

