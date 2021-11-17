#pragma once
class MainGame
{
private:
    
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
    void TextRender();//그리기
};

