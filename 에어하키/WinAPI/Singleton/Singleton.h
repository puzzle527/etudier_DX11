#pragma once
template <typename T>
class Singleton
{
protected:
    //��ӹ޴� Ŭ�������� �������� ���Ե� ���
    static T* Instance;
    Singleton() {};
    ~Singleton() {};
public:
    static T* GetInstance(); //���Լ�
    void DeleteSingleton(); //�����Ͱ� ����Ű�� �޸�����
};
//cpp����� ���⼭ �ʱ�ȭ
template<typename T>
T * Singleton<T>::Instance = nullptr;



template<typename T>
T* Singleton<T>::GetInstance()
{
    //�ν��Ͻ��� ��ü�� �Ҵ��� �ȵ�������
    if(!Instance)
    {
        Instance = new T;
    }
    return Instance;
}

template<typename T>
void Singleton<T>::DeleteSingleton()
{
    if(Instance)
    {
        delete Instance;
        Instance = nullptr;
    };
}
