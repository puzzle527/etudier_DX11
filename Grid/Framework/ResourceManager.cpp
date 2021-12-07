#include "Framework.h"
#include "ResourceManager.h"

shared_ptr<Shader> ResourceManager::LoadShader(string file, VertexType vertextype)
{
	auto iter = Shaders.find(file);
	shared_ptr<Shader> temp;
	//존재함
	if (iter != Shaders.end())
	{
		return iter->second;
	}
	else
	{
		temp = make_shared<Shader>();
		temp->CreateFromFile(file, vertextype);
		Shaders[file] = temp;
	}

	return temp;
}

shared_ptr<Mesh> ResourceManager::LoadMesh(string file)
{
	auto iter = Meshes.find(file);
	shared_ptr<Mesh> temp;
	//존재함
	if (iter != Meshes.end())
	{
		return iter->second;
	}
	else
	{
		temp = make_shared<Mesh>();
		temp->CreateFromFile(file);
		Meshes[file] = temp;
	}

	return temp;
}

//void ResourceManager::SaveMesh(string file, shared_ptr<Mesh> mesh)
//{
//}

void ResourceManager::ReleaseResource()
{
	for (auto it = Shaders.begin(); it != Shaders.end(); it++)
	{
		it->second.reset();
	}

}
