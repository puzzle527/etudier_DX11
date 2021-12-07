#include "Framework.h"
#include "GameObject.h"
#pragma region StaticTransform
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
#pragma endregion

#pragma region 기본생성자
GameObject::GameObject(string Name)
    : super(nullptr), parent(nullptr), mesh(nullptr), name(Name)
    , isAxis(false) , isVisible(true)
    //멤버 이니셜라이즈
{
    mesh = RESOURCE->LoadMesh("Point");
    //mesh = make_shared<Mesh>();
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
GameObject* GameObject::Create(string Name)
{
    return new GameObject(Name);
}
Actor* Actor::Create(string Name)
{
    return new Actor(Name);
}
#pragma endregion

#pragma region 복사생성자
GameObject::GameObject(GameObject& src)
{
    mesh = src.mesh;
    shader = src.shader;
    type = src.type;
    name = src.name;
    isVisible = src.isVisible;
    isAxis = src.isAxis;
    position = src.position;
    scale = src.scale;
    rotation = src.rotation;
    //연결 포인터 제외
}
void GameObject::CopyChild(GameObject* src)
{
    //내가 이미 생성된후
    for (auto it = src->child.begin(); it != src->child.end(); it++)
    {
        GameObject* Child;
        GameObject* srcChild = it->second;
        //Child 생성
        Child = new GameObject(*srcChild);
        //주소연결
        Child->super = this->super;
        Child->parent = this;
        child[Child->name] = Child;
        //테이블연결
        super->AddObject(Child);
        //자식의 재귀호출
        Child->CopyChild(srcChild);
    }
}
Actor::Actor(Actor& src)
    :GameObject(src)
{
    super = this;
    parent = nullptr;
    obList[src.name] = this;
    type = OBTYPE::ACTOR;
}
Actor* Actor::Create(Actor* src)
{
    Actor* temp = new Actor(*src);
    temp->CopyChild(src);
    return temp;
}
void Actor::Copy(Actor* src)
{
    ReleaseMember();
    super = this;
    parent = nullptr;
    obList[src->name] = this;
    mesh = src->mesh;
    shader = src->shader;
    type = src->type;
    name = src->name;
    isVisible = src->isVisible;
    isAxis = src->isAxis;
    type = OBTYPE::ACTOR;
    position = src->position;
    scale = src->scale;
    rotation = src->rotation;
    CopyChild(src);
}
#pragma endregion

#pragma region 소멸
GameObject::~GameObject()
{
    mesh.reset();
    shader.reset();
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
Actor::~Actor()
{

}
void Actor::ReleaseMember()
{
    //내가 가진거 전부 해제
    for (auto it = child.begin(); it != child.end(); it++)
    {
        it->second->Release();
    }
    mesh.reset();
    shader.reset();
    obList.clear();
    child.clear();
}
#pragma endregion

#pragma region GameObject
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
    if (isVisible)
    {
        mesh->Set();
        shader->Set();
        D3D->GetDC()->DrawIndexed(mesh->indexCount, 0, 0);
    }
    if (isAxis)
    {
        trans->W = W;
        trans->Render();
    }
    for (auto it = child.begin(); it != child.end(); it++)
    {
        it->second->Render();
    }
}

bool GameObject::ImGuiRender()
{
    Gui::IDSet();
    if (ImGui::TreeNode(name.c_str()))
    {
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Transform"))
            {
                ImGui::Checkbox("isAxis", &isAxis);
                ImGui::SameLine();
                ImGui::Checkbox("isVisible", &isVisible);
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
                    ImGui::PopID();
                    return false;
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
                        ImGui::PopID();
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
                    ImGui::InputText("ApplyFile", FileName, sizeof(FileName));
                    if (ImGui::Button("Save"))
                    {
                        dynamic_cast<Actor*>(this)->SaveFile(FileName);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Load"))
                    {
                        RESOURCE->LoadCam(FileName, dynamic_cast<Actor*>(this));
                    }
                    ImGui::EndTabItem();
                }
            }
            if (type == OBTYPE::ACTOR)
            {
                if (ImGui::BeginTabItem("Actor"))
                {
                    ImGui::InputText("ApplyFile", FileName, sizeof(FileName));
                    if (ImGui::Button("Save"))
                    {
                        dynamic_cast<Actor*>(this)->SaveFile(FileName);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Load"))
                    {
                        RESOURCE->LoadActor(FileName, dynamic_cast<Actor*>(this));
                    }
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
                ImGui::PopID();
                return false;
            }
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
    return true;
}
#pragma endregion

#pragma region Actor
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
#pragma endregion

#pragma region SaveLoad
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
    This->SetAttribute("isVisible", isVisible);
    This->SetAttribute("isAxis", isAxis);

    if (type == OBTYPE::CAM)
    {
        Xml::XMLElement* Cam = doc->NewElement("Cam");
        This->LinkEndChild(Cam);
        Camera* CamOb = dynamic_cast<Camera*>(this);
        Cam->SetAttribute("Fov", CamOb->Fov);
        Cam->SetAttribute("Near", CamOb->Near);
        Cam->SetAttribute("Far", CamOb->Far);
    }

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

    ReleaseMember();

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
    isVisible = This->BoolAttribute("isVisible");
    isAxis = This->BoolAttribute("isAxis");

    if (type == OBTYPE::CAM)
    {
        Camera* CamOb = dynamic_cast<Camera*>(this);
        component = This->FirstChildElement("Cam");
        CamOb->Fov = component->FloatAttribute("Fov");
        CamOb->Near = component->FloatAttribute("Near");
        CamOb->Far = component->FloatAttribute("Far");
    }

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
#pragma endregion