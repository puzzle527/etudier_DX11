#pragma once
class CamManager : public Singleton<CamManager>
{
private:
    Matrix              V;          //뷰 행렬        
    ID3D11Buffer*		VBuffer;    //뷰 버퍼

    Matrix              P;          //프로젝션 행렬
    ID3D11Buffer*		PBuffer;    //프로젝션 버퍼
public:

    CamManager();
    ~CamManager();
    //                  카메라가 갱신되어 바인드 되도록
    void                CameraUpdate();
    //카메라위치
    Vector2             Pos;
  
};

