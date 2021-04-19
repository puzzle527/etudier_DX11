#pragma once
template <typename T>
class Singleton
{
    //��ӹ޴� Ŭ�������� �����̵Ǵ�
protected:
    static T* Instance;
    Singleton() {};
    ~Singleton() {};
public:
    static T* GetInstance(); //���Լ�
    void DeleteSingleton(); //�����Ͱ� ����Ű�� �޸�����
};

//cpp����� ���⼭ �ʱ�ȭ
template<typename T>
T* Singleton<T>::Instance = nullptr;



template<typename T>
T* Singleton<T>::GetInstance()
{
  

    // !3 -> 0
    // !0 -> 1
    // !'a' ->0
    // !0x8000c ->0
    // !nullptr ->1

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

//template <typename T>
//void Swap(T& a, T&b)
//{
//
//}