#pragma once
class GameObject : public Transform
{
    //������ƮX
public:
    GameObject();
    Mesh* mesh;
    //�ݶ��̴�
    //���͸���

    //key,
    string name;
    //Ʈ������
    unordered_map<string, GameObject*> child;

    void ImGuiRender() override;

    //����
    bool AddChild(GameObject*& Child);//�����ڽ��� �̸��� �Ȱ�ġ�� �߰�
    GameObject* FindObject(string Name);
};

