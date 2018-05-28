#include <Engine/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Lib/stb_image.h>

#include <iostream>

Texture::Texture() : m_width(-1), m_height(-1), m_nrChannels(-1), m_texture(0)
{

}

Texture::Texture(std::string filePath) : m_width(-1), m_height(-1), m_nrChannels(-1), m_texture(0)
{
	Load(filePath);
}

Texture::~Texture()
{
	Unload();
}

void Texture::Load(std::string filePath)
{
	Unload();
	unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	if (data)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
		data = nullptr;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		assert(false);
	}
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}