#pragma once
class Line; //전방선언
class Object
{
protected:

    Matrix  T; //이동행렬
    Matrix  S; //크기행렬
    Matrix  R; //자전 회전행렬(z축)
    Matrix  R2; //공전 회전행렬(z축)

    Matrix  W; //월드행렬

    

    Shader*				shader;  //쉐이더
    ID3D11Buffer*		WBuffer; //자원
    ID3D11Buffer*		ColorBuffer;

public:
    //활성화된 오브젝트 인가?
    bool        isActive = true;
    Vector2		Pivot = Vector2(0, 0);
    Vector2     WorldPivot;
    Matrix  RT; //회전이동행렬
    Matrix* P; // 부모행렬
    static Line*  Axis; //축,원점
    bool    isAxis = false; //축을 그릴거냐?
    Vector2 Up, Right; //방향
    Vector2 Position;//위치값,원점 (로컬)
    Vector2 Scale; //크기
    Vector3 Rotation; //자전값 (x,y,z 축)
    Vector3 Rotation2;//공전값
    //섞어줄 색
    Color   color = Color(0.5f, 0.5f, 0.5f, 0.5f);


    Object();
    virtual ~Object();
    virtual void Init();
    virtual void WorldUpdate();
    virtual void Render();
    Vector2 GetWorldPos() { return Vector2(W._41, W._42); }
};

