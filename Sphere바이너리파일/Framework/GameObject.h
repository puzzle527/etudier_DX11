#pragma once
class Actor;
//트리구조
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
    virtual ~GameObject(); //본인이 들고있는 멤버만 삭제
public:
    static GameObject* Create(string Name = " ");
   
    virtual void Release(); //하위자식들까지 전부 삭제
    virtual bool AddChild(GameObject* Child);
    virtual void Render();
    virtual void Update();
    virtual bool ImGuiRender() override;
};

//해쉬테이블관련 Root
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