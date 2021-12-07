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
    static Camera* Create(string Name = "Camera");
    static void CreateBuffer();
    static void ReleaseBuffer();
    virtual bool ImGuiRender() override;
    virtual void Update() override;
    virtual void Set() override;
};

