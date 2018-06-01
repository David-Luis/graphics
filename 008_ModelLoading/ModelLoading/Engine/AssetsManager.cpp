#include <Engine/AssetsManager.h>

#include <Engine/Texture.h>

void AssetsManager::LoadTexture(std::string path)
{
	if (m_textures.find(path) == m_textures.end())
	{
		Texture* texture = new Texture();
		texture->LoadFromFile(path);
		m_textures.insert({ path, texture });
	}
}

Texture* AssetsManager::GetTexture(std::string path)
{
	if (m_textures.find(path) != m_textures.end())
	{
		return m_textures.at(path);
	}

	return nullptr;
}