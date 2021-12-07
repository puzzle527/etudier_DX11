#pragma once
class ResourceManager : public Singleton<ResourceManager>
{
private:
	//file ���� ����Ʈ�� ����Ʈ������
	unordered_map<string, shared_ptr<Shader>>	Shaders;
	unordered_map<string, shared_ptr<Mesh>>		Meshes;
	



	//transform�� ������ ��ü�� �׳� ������
	unordered_map<string, GameObject*>			Objects;

public:
	shared_ptr<Shader>	LoadShader(string file, VertexType vertextype);
	shared_ptr<Mesh>	LoadMesh(string file);
	GameObject*			LoadObject(string file);
	void ReleaseResource();
};

