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
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (size_t i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); 
										  
		std::string number;
		std::string name = m_textures[i]->GetType();
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		name = "material." + name + "_" + number;
		shader.SetInt(name, static_cast<int>(i));
		glBindTexture(GL_TEXTURE_2D, m_textures[i]->GetId());
	}
}