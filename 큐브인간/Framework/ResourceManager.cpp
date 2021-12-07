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
		temp->LoadFile(file, vertextype);
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
		temp->LoadFile(file);
		Meshes[file] = temp;
	}

	return temp;
}

Actor* ResourceManager::LoadActor(string file)
{
	auto iter = Actors.find(file);
	Actor* temp;
	//존재함
	if (iter != Actors.end())
	{
		temp = Actor::Create(iter->second);
		return temp;
	}
	else
	{
		temp = Actor::Create();
		temp->LoadFile(file);
		Actors[file] = temp;
	}

	return temp;
}

Actor* ResourceManager::LoadActor(string file, Actor* This)
{
	auto iter = Actors.find(file);
	//존재함
	if (iter != Actors.end())
	{
		This->Copy(iter->second);
		return This;
	}
	else
	{
		This->LoadFile(file);
		Actors[file] = This;
	}

	return This;
}

Camera* ResourceManager::LoadCam(string file)
{
	auto iter = Actors.find(file);
	Camera* temp;
	//존재함
	if (iter != Actors.end())
	{
		temp = Camera::Create();
		temp->LoadFile(file);
		return temp;
	}
	else
	{
		temp = Camera::Create();
		temp->LoadFile(file);
		Actors[file] = temp;
	}

	return temp;
}

Camera* ResourceManager::LoadCam(string file, Actor* This)
{
	auto iter = Actors.find(file);
	//존재함
	if (iter != Actors.end())
	{
		This->LoadFile(file);
		return dynamic_cast<Camera*>(This);
	}
	else
	{
		This->LoadFile(file);
		Actors[file] = This;
	}

	return dynamic_cast<Camera*>(This);
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
