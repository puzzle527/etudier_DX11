#pragma once
template <typename T>
class Singleton
{
    //상속받는 클래스에게 접근이되는
protected:
    static T* Instance;
    Singleton() {};
    ~Singleton() {};
public:
    static T* GetInstance(); //겟함수
    void DeleteSingleton(); //포인터가 가르키는 메모리해제
};

//cpp가없어서 여기서 초기화
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

      //인스턴스의 객체가 할당이 안되있으면
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