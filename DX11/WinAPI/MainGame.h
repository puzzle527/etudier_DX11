#pragma once
class MainGame
{
private:
    //현재 씬
    Scene* CurrentScene = nullptr;
   
    //교체할 씬
    Scene* sc1;
    Scene* sc2;

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

