#pragma once
class Camera :public GameObject
{
    Matrix View, Proj;
    static ID3D11Buffer* VBuffer;
    static ID3D11Buffer* PBuffer;
   
protected:
    Camera(string Name);
    virtual ~Camera();
public:
    float   Fov, Near, Far;
    static Camera* Create(string Name = "Camera");
    static void CreateBuffer();
    static void ReleaseBuffer();
    void CamImGuiRender();
    virtual void Update() override;
    virtual void Set() override;
};

