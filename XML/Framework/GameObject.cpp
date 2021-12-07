#include "Framework.h"
#include "GameObject.h"


GameObject::GameObject(string Name)
    : super(nullptr), parent(nullptr), mesh(nullptr), name(Name)      //멤버 이니셜라이즈
{
    //mesh = make_shared<Mesh>();
    mesh = RESOURCE->LoadMesh("Point");
    shader = RESOURCE->LoadShader("2.Cube", VertexType::V_PC);
    type = OBTYPE::OBJECT;
}



Actor::Actor(string Name)
    : GameObject(Name)
{
    super = this;
    parent = nullptr;
    obList[Name] = this;
    type = OBTYPE::ACTOR;
}


GameObject::~GameObject()
{
    mesh.reset();
    shader.reset();
}
Actor::~Actor()
{
    //int a = 0;
}

GameObject* GameObject::Create(string Name)
{
    return new GameObject(Name);
}
Actor* Actor::Create(string Name)
{
    return new Actor(Name);
}
GameObject* GameObject::trans = nullptr;

void GameObject::CreateTrans()
{
    trans = GameObject::Create("Trans");
    trans->mesh = RESOURCE->LoadMesh("Transform");
    trans->shader = RESOURCE->LoadShader("2.Cube", VertexType::V_PC);
}
void GameObject::ReleaseTrans()
{
    SafeRelease(trans);

}



void GameObject::Release()
{
    // L-R-Root

    for (auto it = child.begin(); it != child.end(); it++)
    {
        SafeRelease(it->second);
    }
    //delete 동적할당해제기때문에 new를 반드시 쓴 객체만 지워야함
    delete this;
}




GameObject* Actor::FindObject(string Name)
{
    auto temp = obList.find(Name);
    if (temp != obList.end())
    {
        return temp->second;
    }
    return nullptr;
}
bool Actor::AddObject(GameObject* object)
{
    if (FindObject(object->name))
    {
        return false;
    }
    obList[object->name] = object;
    return true;
}
bool Actor::DeleteObject(string Name)
{
    //중간삭제는 root삭제 불가
    if (Name == name)
    {
        return false;
    }
    //키가 테이블에 없을때도 삭제 불가
    auto temp = obList.find(Name);
    if (temp == obList.end())
    {
        return false;
    }

    //지워질대상,지워질대상의 부모 포인터
    GameObject* Target = temp->second;
    GameObject* Parent = temp->second->parent;
    //부모리스트에서 타겟 비우기
    Parent->child.erase(Parent->child.find(Name));

    for (auto it = Target->child.begin(); it != Target->child.end(); it++)
    {
        Parent->child[it->second->name] = it->second;
        it->second->parent = Parent;
    }
    SafeDelete(Target);
    return true;
}
bool GameObject::AddChild(GameObject* Child)
{
    //하위자식이 겹친다면
    if (super->FindObject(Child->name))
    {
        return false;
    }
    Child->super = super;
    Child->parent = this;
    child[Child->name] = Child;
    super->AddObject(Child);
    return true;
}



void GameObject::Update()
{
    if (parent)
        Transform::Update(parent);
    else
        Transform::Update();

    for (auto it = child.begin(); it != child.end(); it++)
    {
        it->second->Update();
    }
}

void GameObject::Render()
{
    Transform::Set();
    if (mesh)
    {
        mesh->Set();
        shader->Set();
        D3D->GetDC()->DrawIndexed(mesh->indexCount, 0, 0);
        if (isDebug )
        {
            trans->W = W;
            trans->Render();
        }
    }
   

    for (auto it = child.begin(); it != child.end(); it++)
    {
        it->second->Render();
    }
}

bool GameObject::ImGuiRender()
{
    if (ImGui::TreeNode(name.c_str()))
    {
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Transform"))
            {
                ImGui::Checkbox("isAxis", &isDebug);
                Transform::ImGuiRender();
                ImGui::InputText("ChildName", childName, sizeof(childName));
                if (ImGui::Button("AddChild"))
                {
                    AddChild(new GameObject(childName));
                }
                ImGui::SameLine();
                if (ImGui::Button("Delete"))
                {
                    super->DeleteObject(name);
                    ImGui::EndTabItem();
                    ImGui::EndTabItem();
                    ImGui::TreePop();
                    return false;
                }
                if (type == OBTYPE::ACTOR)
                {
                    ImGui::InputText("ApplyFile", FileName, sizeof(FileName));
                    if (ImGui::Button("Save"))
                    {
                        dynamic_cast<Actor*>(this)->SaveFile(FileName);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Load"))
                    {
                        //dynamic_cast<Actor*>(this)->LoadFile(FileName);
                        RESOURCE->LoadActor(FileName, dynamic_cast<Actor*>(this));
                    }
                }
                
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Mesh"))
            {
                if (mesh)
                {
                    ImGui::InputText("ApplyFile", meshName, sizeof(meshName));
                    if (ImGui::Button("Save"))
                    {
                        mesh->SaveFile(meshName);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Load"))
                    {
                        mesh = RESOURCE->LoadMesh(meshName);
                        ImGui::EndTabItem();
                        ImGui::EndTabItem();
                        ImGui::TreePop();
                        return false;
                    }
                }
                else
                {
                    ImGui::Text("None");
                }
                ImGui::EndTabItem();
            }
            if (type == OBTYPE::CAM)
            {
                if (ImGui::BeginTabItem("Cam"))
                {
                    dynamic_cast<Camera*>(this)->CamImGuiRender();
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
        for (auto it = child.begin(); it != child.end();)
        {
            if (it->second->ImGuiRender())
            {
                //현재프레임에서 하위자식을 지우지않는한
                it++;//반복하며 렌더하겠다
            }
            else
            {
                ImGui::TreePop();
                return false;
            }
        }
        ImGui::TreePop();
    }
    return true;
}

void Actor::SaveFile(string File)
{
    //관리자
    Xml::XMLDocument* doc = new Xml::XMLDocument();

    Xml::XMLElement* ob = doc->NewElement("Root");
    doc->LinkEndChild(ob);
    SaveObject(ob, doc);

    string path = "../Contents/GameObject/" + File + ".xml";
    doc->SaveFile(path.c_str());

    SafeDelete(doc);
}



void GameObject::SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc)
{
    //key
    This->SetAttribute("Name", name.c_str());
    This->SetAttribute("Type", (int)type);

    //Mesh
    Xml::XMLElement* Mesh = doc->NewElement("Mesh");
    This->LinkEndChild(Mesh);
    Mesh->SetAttribute("File", mesh->file.c_str());

    //Shader
    Xml::XMLElement* Shader = doc->NewElement("Shader");
    This->LinkEndChild(Shader);
    Shader->SetAttribute("File", shader->file.c_str());
    Shader->SetAttribute("VertexType", (int)shader->vertextype);

    //Transform
    Xml::XMLElement* Transform = doc->NewElement("Transform");
    This->LinkEndChild(Transform);


    Xml::XMLElement* Position = doc->NewElement("Position");
    Transform->LinkEndChild(Position);
    Position->SetAttribute("X", position.x);
    Position->SetAttribute("Y", position.y);
    Position->SetAttribute("Z", position.z);

    Xml::XMLElement* Scale = doc->NewElement("Scale");
    Transform->LinkEndChild(Scale);
    Scale->SetAttribute("X", scale.x);
    Scale->SetAttribute("Y", scale.y);
    Scale->SetAttribute("Z", scale.z);

    Xml::XMLElement* Rotation = doc->NewElement("Rotation");
    Transform->LinkEndChild(Rotation);
    Rotation->SetAttribute("X", rotation.x);
    Rotation->SetAttribute("Y", rotation.y);
    Rotation->SetAttribute("Z", rotation.z);

    Xml::XMLElement* Children = doc->NewElement("Children");
    This->LinkEndChild(Children);
    Children->SetAttribute("Size", (int)child.size());

    //child
    int i = 0;
    for (auto it = child.begin(); it != child.end(); it++)
    {
        string Tag = "Child" + to_string(i);
        Xml::XMLElement* ob = doc->NewElement(Tag.c_str());
        This->LinkEndChild(ob);
        it->second->SaveObject(ob, doc);
        i++;
    }
}


void Actor::LoadFile(string File)
{

    //관리자
    Xml::XMLDocument* doc = new Xml::XMLDocument();
    string path = "../Contents/GameObject/" + File + ".xml";
    
    Xml::XMLError result = doc->LoadFile(path.c_str());
    if (result != Xml::XML_SUCCESS) return;

    //내가 가진거 전부 해제
    for (auto it = child.begin(); it != child.end(); it++)
    {
        it->second->Release();
    }
    mesh.reset();
    shader.reset();

    obList.clear();
    child.clear();


    Xml::XMLElement* ob;

    ob = doc->FirstChildElement();
    name = ob->Attribute("Name");
    obList[name] = this;
    LoadObject(ob, doc);

    SafeDelete(doc);
}

void GameObject::LoadObject(Xml::XMLElement* This, Xml::XMLDocument* doc)
{
    Xml::XMLElement* component;
    Xml::XMLElement* transform;
    string file; int vertype;

    type = (OBTYPE)This->IntAttribute("Type");

    component = This->FirstChildElement("Mesh");
    file = component->Attribute("File");
    mesh = RESOURCE->LoadMesh(file);

    component = This->FirstChildElement("Shader");
    file = component->Attribute("File");
    vertype = component->IntAttribute("VertexType");
    shader = RESOURCE->LoadShader(file, (VertexType)vertype);

    component = This->FirstChildElement("Transform");
    transform = component->FirstChildElement("Position");
    position.x = transform->FloatAttribute("X");
    position.y = transform->FloatAttribute("Y");
    position.z = transform->FloatAttribute("Z");

    transform = component->FirstChildElement("Scale");
    scale.x = transform->FloatAttribute("X");
    scale.y = transform->FloatAttribute("Y");
    scale.z = transform->FloatAttribute("Z");
    transform = component->FirstChildElement("Rotation");
    rotation.x = transform->FloatAttribute("X");
    rotation.y = transform->FloatAttribute("Y");
    rotation.z = transform->FloatAttribute("Z");

    //child.resize(5);
    component = This->FirstChildElement("Children");
    int size = component->IntAttribute("Size");
    
    for (int i = 0; i != size; i++)
    {
        string Tag = "Child" + to_string(i);
        Xml::XMLElement* ob = This->FirstChildElement(Tag.c_str());
        string childName = ob->Attribute("Name");
        GameObject* temp = GameObject::Create(childName);
        AddChild(temp);
        temp->LoadObject(ob, doc);
    }
}
