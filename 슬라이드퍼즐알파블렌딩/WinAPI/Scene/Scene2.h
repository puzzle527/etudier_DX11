#pragma once

class Scene2 : public Scene
{
private:
    //퍼즐판
    Image* Puzzle[3][3];
    //비어있는 좌표
    Int2   Null;


public:
    HRESULT Init() override;//초기화
    void Release() override;//해제


    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기
};

