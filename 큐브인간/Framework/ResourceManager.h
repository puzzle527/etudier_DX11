#pragma once
class ResourceManager : public Singleton<ResourceManager>
{
private:
	//file ���� ����Ʈ�� ����Ʈ������
	unordered_map<string, shared_ptr<Shader>>	Shaders;
	unordered_map<string, shared_ptr<Mesh>>		Meshes;
	



	//transform�� ������ ��ü�� �׳� ������
	unordered_map<string, Actor*>				Actors;

public:
	shared_ptr<Shader>	LoadShader(string file, VertexType vertextype);
	shared_ptr<Mesh>	LoadMesh(string file);
	Actor*				LoadActor(string file);
	Actor*				LoadActor(string file, Actor* This);
	Camera*				LoadCam(string file);
	Camera*				LoadCam(string file, Actor* This);
	void				ReleaseResource();
};

