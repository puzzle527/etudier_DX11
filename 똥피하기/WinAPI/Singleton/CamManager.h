#pragma once
class CamManager : public Singleton<CamManager>
{
private:
    Matrix              V;          //�� ���        
    ID3D11Buffer*		VBuffer;    //�� ����

    Matrix              P;          //�������� ���
    ID3D11Buffer*		PBuffer;    //�������� ����
public:

    CamManager();
    ~CamManager();
    //                  ī�޶� ���ŵǾ� ���ε� �ǵ���
    void                CameraUpdate();
    //ī�޶���ġ
    Vector2             Pos;
  
};

