#pragma once
class Actor;

enum class OBTYPE
{
    OBJECT,
    ACTOR,
    CAM,
    LIGHT
};


//트리구조
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
    virtual ~GameObject(); //본인이 들고있는 멤버만 삭제
public:
   
    static GameObject*  Create(string Name = " ");
    static void         CreateTrans();
    static void         ReleaseTrans();
    virtual void        Release(); //하위자식들까지 전부 삭제
    virtual bool        AddChild(GameObject* Child);
    virtual void        Render();
    virtual void        Update();
    virtual bool        ImGuiRender() override;

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
    static Actor*   Create(string Name = "Root");
    //static Actor*   Create(string File = "Root");
    GameObject*     FindObject(string Name);
    bool            AddObject(GameObject* object);
    bool            DeleteObject(string Name);
    virtual void    SaveFile(string File);
    virtual void    LoadFile(string File);
};