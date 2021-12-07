#pragma once
class Actor;

enum class OBTYPE
{
    OBJECT,
    ACTOR,
    CAM,
    LIGHT
};


//Ʈ������
class GameObject : public Transform
{
    friend Actor;
    //valiable
private:
    char                    childName[32] = "None";
    char                    meshName[32] = "Cube";
    char                    FileName[32] = "Object";
    static GameObject*      trans;
protected:

    //key
    string                  name;
    OBTYPE                  type;

    //member
    bool                    isDebug = false;
    shared_ptr<Mesh>        mesh;
    shared_ptr<Shader>      shader;


    //pointer
    Actor*                  super;
    GameObject*             parent;
    map<string,GameObject*> child;
   
    
    //Function
protected:
    virtual void SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
    virtual void LoadObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
    GameObject(string Name);
    virtual ~GameObject(); //������ ����ִ� ����� ����
public:
   
    static GameObject*  Create(string Name = " ");
    static void         CreateTrans();
    static void         ReleaseTrans();
    virtual void        Release(); //�����ڽĵ���� ���� ����
    virtual bool        AddChild(GameObject* Child);
    virtual void        Render();
    virtual void        Update();
    virtual bool        ImGuiRender() override;

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
    static Actor*   Create(string Name = "Root");
    //static Actor*   Create(string File = "Root");
    GameObject*     FindObject(string Name);
    bool            AddObject(GameObject* object);
    bool            DeleteObject(string Name);
    virtual void    SaveFile(string File);
    virtual void    LoadFile(string File);
};