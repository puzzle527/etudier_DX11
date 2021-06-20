#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
    //���� �ý��� ����
    System_Create(&system);
    //���� ä�μ� ����
    system->init(TOTALSOUNDBUFFER,
        FMOD_INIT_NORMAL, 0);
    //���� ä�� �����Ҵ�
    sound = new Sound * [TOTALSOUNDBUFFER];
    channel = new Channel * [TOTALSOUNDBUFFER];
    ZeroMemory(sound, sizeof(Sound*) * TOTALSOUNDBUFFER);
    ZeroMemory(channel, sizeof(Channel*) * TOTALSOUNDBUFFER);

}

SoundManager::~SoundManager()
{
    for (int i = 0; i < TOTALSOUNDBUFFER; i++)
    {
        if (channel != nullptr)
        {
            if (channel[i]) channel[i]->stop();
        }

        if (sound != nullptr)
        {
            if (sound[i]) sound[i]->release();
        }
    }


    delete[] channel;
    delete[] sound;

    system->release();
    system->close();
    SoundMap.clear();
    ChannelMap.clear();

}

bool SoundManager::AddSound(string File, string Key, bool loop)
{
    //�ߺ��� Ű�� ������
    if (SoundMap.find(Key) !=
        SoundMap.end())//Ž������� ������ end��ȯ
    {
        return false;
    }
    string add = "./Sound/";
    add = add + File;
    if (loop)
    {
        system->createStream(add.c_str(), FMOD_LOOP_NORMAL, nullptr,
            &sound[SoundMap.size()]);
    }
    else
    {
        system->createStream(add.c_str(), FMOD_DEFAULT, nullptr,
            &sound[SoundMap.size()]);
    }
    SoundMap[Key] = sound[SoundMap.size()];
    ChannelMap[Key] = channel[ChannelMap.size()];
    return true;
}

void SoundManager::Play(string Key)
{
    //�ߺ��� Ű�� ������
    if (SoundMap.find(Key) !=
        SoundMap.end())
    {
        system->playSound(FMOD_CHANNEL_FREE,
            SoundMap[Key], false,
            &ChannelMap[Key]);
    }
}

void SoundManager::Stop(string Key)
{
    //�ߺ��� Ű�� ������
    if (ChannelMap.find(Key) !=
        ChannelMap.end())
    {
        ChannelMap[Key]->stop();
    }
}

void SoundManager::Pause(string Key)
{
    //�ߺ��� Ű�� ������
    if (ChannelMap.find(Key) !=
        ChannelMap.end())
    {
        ChannelMap[Key]->setPaused(true);
    }
}

void SoundManager::Resume(string Key)
{
    //�ߺ��� Ű�� ������
    if (ChannelMap.find(Key) !=
        ChannelMap.end())
    {
        ChannelMap[Key]->setPaused(false);
    }
}

void SoundManager::SetVolume(string Key, float scale)
{
    //�ߺ��� Ű�� ������
    if (ChannelMap.find(Key) !=
        ChannelMap.end())
    {
        ChannelMap[Key]->setVolume(scale);
    }
}

void SoundManager::Update()
{
    //���������� �����Լ� ȣ��
    system->update();
}
