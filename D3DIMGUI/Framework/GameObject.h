#pragma once
class GameObject : public Transform
{
    //컴포넌트X
public:
    GameObject();
    Mesh* mesh;
    //콜라이더
    //머터리얼

    //key,
    string name;
    //트리구조
    unordered_map<string, GameObject*> child;

    void ImGuiRender() override;

    //과제
    bool AddChild(GameObject*& Child);//하위자식이 이름이 안겹치면 추가
    GameObject* FindObject(string Name);
};

