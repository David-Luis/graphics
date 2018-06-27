#include <Engine/Texture/CTextureSet.h>

#include <Engine/Texture/CTexture.h>
#include <Engine/Shader/CShader.h>

#include <glad/glad.h>

CTextureSet::CTextureSet(std::vector<CTexture*> textures)
{
	m_textures = textures;
}

void CTextureSet::Use(const CShader& shader) const
{
	for (size_t i = 0; i < m_textures.size(); i++)
	{
		m_textures[i]->Use(shader, i);
	}
}