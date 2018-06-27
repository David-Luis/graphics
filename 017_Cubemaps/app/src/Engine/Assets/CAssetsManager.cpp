#include <Engine/Assets/CAssetsManager.h>

#include <Engine/Texture/CTexture.h>

CTexture* CAssetsManager::LoadTexture(std::string path)
{
	CTexture* texture;
	if (m_textures.find(path) == m_textures.end())
	{
		texture = new CTexture();
		texture->LoadFromFile(path);
		m_textures.insert({ path, texture });
	}
	else
	{
		texture = GetTexture(path);
	}

	return texture;
}

CTexture* CAssetsManager::GetTexture(std::string path)
{
	if (m_textures.find(path) != m_textures.end()) 
	{
		return m_textures.at(path);
	}

	return nullptr;
}