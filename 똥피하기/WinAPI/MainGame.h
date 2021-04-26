#pragma once
class MainGame
{
private:
   Scene* pCurrentScene = nullptr;
   //스위치 될 씬
   Scene* sc1;
   Scene* sc2;
   bool   isVsync; //수직동기화 할건지
public:
    MainGame();//생성
    ~MainGame();//소멸

    HRESULT Init();//초기화
    void Release();//해제

    //루프
    void Update();//갱신
    void LateUpdate();//늦은갱신
    void Render();//그리기
};

