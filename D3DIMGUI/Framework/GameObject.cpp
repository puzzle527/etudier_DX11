#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject() 
    :mesh(nullptr)
{
}

void GameObject::ImGuiRender()
{
    if (ImGui::TreeNode(name.c_str()))
    {
        ImGui::Text("Transform");
        Transform::ImGuiRender();
        for (auto it = child.begin(); it != child.end(); it++)
        {
            it->second->ImGuiRender();
        }
        ImGui::TreePop();
    }
}

bool GameObject::AddChild(GameObject*& Child)
{
    return false;
}

GameObject* GameObject::FindObject(string Name)
{
    // TODO: ���⿡ return ���� �����մϴ�.
    return nullptr;
}
