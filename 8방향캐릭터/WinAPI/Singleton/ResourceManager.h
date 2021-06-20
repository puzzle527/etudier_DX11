#pragma once
class ResourceManager :public Singleton<ResourceManager>
{
private:
    map<_tstring, ID3D11ShaderResourceView*>     SrvMap;

public:
    ResourceManager();
    ~ResourceManager();
    Shader* ShaderArray[2];
    ID3D11ShaderResourceView* LoadTexture(_tstring file);
};

