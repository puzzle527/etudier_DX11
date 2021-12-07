#pragma once
class ResourceManager : public Singleton<ResourceManager>
{
private:
	//file 단위 임포트는 스마트포인터
	unordered_map<string, shared_ptr<Shader>>	Shaders;
	unordered_map<string, shared_ptr<Mesh>>		Meshes;
	



	//transform을 각각쓸 객체는 그냥 포인터
	unordered_map<string, GameObject*>			Objects;

public:
	shared_ptr<Shader> LoadShader(string file, VertexType vertextype);
	shared_ptr<Mesh> LoadMesh(string file);
	void ReleaseResource();
	//void SaveMesh(string file, shared_ptr<Mesh>mesh);
	/*GameObject* LoadObject(string file);
	bool SaveObject(string file, GameObject* object);
	*/
};

