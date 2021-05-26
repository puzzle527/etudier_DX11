#pragma once
class SceneManager : public Singleton<SceneManager>
{
private:
    //���� ��
    Scene* CurrentScene = nullptr;
    //key�� �񱳿����� �����ؾ��Ѵ�.
    //   key     value
    map<string, Scene*> SceneMap;
    //   key,value
    //set<Scene*> SceneTree;
    //typedef map<string, Scene*>::iterator iter;
public:
    ~SceneManager();
    //�� �߰�
    bool    AddScene(string key, Scene* value);
    //�� ����
    Scene*  ChangeScene(string key);
    //�� ��������
    Scene*  GetScene(string key);
    //���� �� ��������
    Scene*  GetCurrentScene();

};

