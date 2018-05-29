#pragma once

#include <glad/glad.h>

#include <string>

class Texture
{
public:
	Texture();
	Texture(std::string filePath);
	virtual ~Texture();
	Texture(const Texture&) = delete;
	Texture& operator=(Texture const&) = delete;

	virtual void Load(std::string filePath);
	virtual void Unload() { }
	virtual void Use();

private:
	int m_width;
	int m_height;
	int m_nrChannels;
	GLuint m_texture;
};
