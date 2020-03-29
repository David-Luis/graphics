#include <Engine/Texture/CTexture.h>

#include <Engine/Shader/CShader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Lib/stb_image.h>

#include <iostream>

void CTexture::LoadFromFile(const std::string& filePath)
{
	glGenTextures(1, &m_id);

	unsigned char *data = stbi_load(filePath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (m_nrChannels == 1)
			format = GL_RED;
		else if (m_nrChannels == 3)
			format = GL_RGB;
		else if (m_nrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filePath << std::endl;
		stbi_image_free(data);
	}
}

void CTexture::Use(const CShader& shader, GLuint index) const
{
	glActiveTexture(GL_TEXTURE0 + index);

	std::string name = "material." + m_type;
	shader.SetInt(name, static_cast<int>(index));
	glBindTexture(GL_TEXTURE_2D, m_id);
}