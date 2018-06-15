#include <Engine/Assets/CAssetsManager.h>

#include <Engine/Texture/CTexture.h>

void CAssetsManager::LoadTexture(std::string path)
{
	if (m_textures.find(path) == m_textures.end())
	{
		CTexture* texture = new CTexture();
		texture->LoadFromFile(path);
		m_textures.insert({ path, texture });
	}
}

CTexture* CAssetsManager::GetTexture(std::string path)
{
	if (m_textures.find(path) != m_textures.end())
	{
		return m_textures.at(path);
	}

	return nullptr;
}