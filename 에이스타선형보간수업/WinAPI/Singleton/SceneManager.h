#pragma once
class SceneManager : public Singleton<SceneManager>
{
private:
    //현재 씬
    Scene* CurrentScene = nullptr;
    //key는 비교연산이 가능해야한다.
    //   key     value
    map<string, Scene*> SceneMap;
    //   key,value
    //set<Scene*> SceneTree;
    //typedef map<string, Scene*>::iterator iter;
public:
    ~SceneManager();
    //씬 추가
    bool    AddScene(string key, Scene* value);
    //씬 변경
    Scene*  ChangeScene(string key);
    //씬 가져오기
    Scene*  GetScene(string key);
    //현재 씬 가져오기
    Scene*  GetCurrentScene();

};

