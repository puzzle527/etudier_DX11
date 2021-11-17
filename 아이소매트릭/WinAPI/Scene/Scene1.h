#pragma once
//맵에디터 씬
class Scene1 : public Scene
{
private:
    class TileMap* Tm;
   
    int     State;      //타일 상태
    Int2    TileSize;   //타일 갯수
    UINT    ImgIdx;     //몇번째 이미지?
    Int2    Frame;      //바꿔줄 분할좌표
public:
    Scene1();
    ~Scene1();
    HRESULT Init() override;//초기화
    void Release() override;//해제
    
    void Update() override;//갱신
    void LateUpdate() override;//늦은갱신
    void Render() override;//그리기

    //함수로 따로 호출
    
    //리사이즈 버튼
    void ResizeButton();
    //타일맵 이미지 버튼
    void TileImgButton();
    //타일맵 브러시
    void TileBrush();

};

