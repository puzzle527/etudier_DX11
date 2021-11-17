#include "Framework.h"
#include "ResourceManager.h"

shared_ptr<Shader> ResourceManager::LoadShader(string file, VertexType vertextype)
{
	auto iter = Shaders.find(file);
	shared_ptr<Shader> temp;
	//Á¸ÀçÇÔ
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

void ResourceManager::ReleaseResource()
{
	for (auto it = Shaders.begin(); it != Shaders.end(); it++)
	{
		it->second.reset();
	}

}
