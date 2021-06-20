#include "stdafx.h"
#include "SceneManager.h"

SceneManager::~SceneManager()
{
    /*int a;
    auto b = 3.5f;
    auto c = Vector2(1,1);*/
    //for (map<string, Scene*>::iterator i = SceneMap.begin();
    //c++ 11�� �߰� Ÿ���� �ڵ����� ����
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
    //map�� end�� ���� ����.
    //find�Լ��� ã�����ϸ� end��ȯ
    if (SceneMap.find(key) != SceneMap.end())
    {
        return false;//�̹� Ű���� �����Ͽ� �߰����� �ʴ´�.
    }
    //Ʈ���� ����
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
    //Ű�� ���ٸ�
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
