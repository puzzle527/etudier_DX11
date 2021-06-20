#include "stdafx.h"
#include "SceneManager.h"

SceneManager::~SceneManager()
{
    /*int a;
    auto b = 3.5f;
    auto c = Vector2(1,1);*/
    //for (map<string, Scene*>::iterator i = SceneMap.begin();
    //c++ 11에 추가 타입을 자동으로 지정
    for (auto i = SceneMap.begin();
        i != SceneMap.end(); i++)
    {
        //i->first; // key
        //i->second;// value
        if (i->second)
        {
            i->second->Release();
            delete i->second;
        }
    }
    SceneMap.clear();
}

bool SceneManager::AddScene(string key, Scene* value)
{
    //map도 end는 값이 없다.
    //find함수는 찾지못하면 end반환
    if (SceneMap.find(key) != SceneMap.end())
    {
        return false;//이미 키값이 존재하여 추가하지 않는다.
    }
    //트리에 삽입
    SceneMap[key] = value;
    //SceneTree.insert(make_pair(key, value));
    return true;
}

Scene* SceneManager::ChangeScene(string key)
{
    Scene* temp = GetScene(key);
    if (temp)CurrentScene = temp;
    return temp;
}

Scene* SceneManager::GetScene(string key)
{
    //키가 없다면
    if (SceneMap.find(key) ==
        SceneMap.end())
    {
        return nullptr;
    }
    return SceneMap[key];
}

Scene* SceneManager::GetCurrentScene()
{
    return CurrentScene;
}
