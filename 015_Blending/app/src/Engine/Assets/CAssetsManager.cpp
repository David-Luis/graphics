#include <Engine/Assets/CAssetsManager.h>

#include <Engine/Texture/Texture.h>

void CAssetsManager::LoadTexture(std::string path)
{
	if (m_textures.find(path) == m_textures.end())
	{
		Texture* texture = new Texture();
		texture->LoadFromFile(path);
		m_textures.insert({ path, texture });
	}
}

Texture* CAssetsManager::GetTexture(std::string path)
{
	if (m_textures.find(path) != m_textures.end())
	{
		return m_textures.at(path);
	}

	return nullptr;
}