#include "Framework.h"
#include "GameObject.h"


GameObject::GameObject(string Name)
    : super(nullptr), parent(nullptr), mesh(nullptr), name(Name)      //��� �̴ϼȶ�����
{
    mesh = make_shared<Mesh>();
    shader = RESOURCE->LoadShader("2.Cube", VertexType::V_PC);
    mesh = RESOURCE->LoadMesh("Sphere");
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
Actor* Actor::Create(string Name)
{
    return new Actor(Name);
}

void GameObject::Release()
{
    // L-R-Root

    for (auto it = child.begin(); it != child.end(); it++)
    {
        SafeRelease(it->second);
    }
    //delete �����Ҵ������⶧���� new�� �ݵ�� �� ��ü�� ��������
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
    //�߰������� root���� �Ұ�
    if (Name == name)
    {
        return false;
    }
    //Ű�� ���̺� �������� ���� �Ұ�
    auto temp = obList.find(Name);
    if (temp == obList.end())
    {
        return false;
    }

    //���������,����������� �θ� ������
    GameObject* Target = temp->second;
    GameObject* Parent = temp->second->parent;
    //�θ𸮽�Ʈ���� Ÿ�� ����
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
    //�����ڽ��� ��ģ�ٸ�
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
    mesh->Set();
    shader->Set();
    Transform::Set();
    D3D->GetDC()->DrawIndexed(mesh->indexCount, 0, 0);
    if (isDebug)
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
                    ImGui::TreePop();
                    return false;
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Mesh"))
            {
                if (mesh)
                {
                    //ImGui::Text("CurrentFile:");
                    //ImGui::SameLine();
                    //ImGui::Text(meshName);
                    ImGui::InputText("ApplyFile", meshName, sizeof(meshName));
                    if (ImGui::Button("Save"))
                    {
                        mesh->SaveFile(meshName);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Load"))
                    {
                        mesh = RESOURCE->LoadMesh(meshName);
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
                    //((Camera*)this)->CamImGuiRender();
                    dynamic_cast<Camera*>(this)->CamImGuiRender();
                    //Camera::ImGuiRender();


                    ImGui::EndTabItem();
                }
            }

            

            ImGui::EndTabBar();
        }
       

        

        
        for (auto it = child.begin(); it != child.end();)
        {
            if (it->second->ImGuiRender())
            {
                //���������ӿ��� �����ڽ��� �������ʴ���
                it++;//�ݺ��ϸ� �����ϰڴ�
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

