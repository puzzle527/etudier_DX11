#pragma once
class Actor;
//Ʈ������
class GameObject : public Transform
{
    friend Actor;
    //valiable
private:
    char                    childName[32] = "None";
    char                    meshName[32] = "Cube";
protected:
    //key
    string                  name;

    //member
    shared_ptr<Mesh>        mesh;
    shared_ptr<Shader>      shader;


    //pointer
    Actor*                  super;
    GameObject*             parent;
    map<string,GameObject*> child;

    //Function
protected:
    GameObject(string Name);
    virtual ~GameObject(); //������ ����ִ� ����� ����
public:
    static GameObject* Create(string Name = " ");
   
    virtual void Release(); //�����ڽĵ���� ���� ����
    virtual bool AddChild(GameObject* Child);
    virtual void Render();
    virtual void Update();
    virtual bool ImGuiRender() override;
};

//�ؽ����̺���� Root
class Actor : public GameObject
{
private:
    unordered_map<string,GameObject*> obList;
protected:
    Actor(string Name);
    virtual ~Actor();
public:
    static Actor* Create(string Name = "Root");
    GameObject* FindObject(string Name);
    bool AddObject(GameObject* object);
    bool DeleteObject(string Name);
};