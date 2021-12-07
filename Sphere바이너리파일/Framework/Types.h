#pragma once
template <typename T>
class Singleton
{
public:
    virtual ~Singleton() {};
    static T* GetInstance()
    {
        static T* Instance = new T;
        return Instance;
    };
    void DeleteSingleton()
    {
        delete GetInstance();
    };
};
//��Ÿ�����δ� ��ü������� ����.
class Scene
{
public:
	virtual ~Scene() {};
	//���� �س��� �Լ�
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ImGuiRender() = 0;
	virtual void ResizeScreen() = 0;
};
