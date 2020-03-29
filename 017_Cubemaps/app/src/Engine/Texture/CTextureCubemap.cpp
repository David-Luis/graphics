#include <Engine/Texture/CTextureCubemap.h>

#include <Engine/Shader/CShader.h>

#include <Lib/stb_image.h>

#include <iostream>

void CTextureCubemap::LoadFromFile(const std::string& filePath)
{
	std::vector<std::string> faces = GetFacesFromPath(filePath);

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &m_width, &m_height, &m_nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << filePath << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CTextureCubemap::Use(const CShader& shader, GLuint index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	shader.SetInt("cubemap", static_cast<int>(index));
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}

std::vector<std::string> CTextureCubemap::GetFacesFromPath(std::string path)
{
	std::vector<std::string> faces =
	{
		path+"/right.jpg",
		path+"/left.jpg",
		path+"/top.jpg",
		path+"/bottom.jpg",
		path+"/front.jpg",
		path+"/back.jpg"
	};

	return faces;
}