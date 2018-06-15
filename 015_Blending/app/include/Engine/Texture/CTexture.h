#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Texture {

public:
	Texture() {}
	Texture(const Texture&) = delete;
	Texture& operator=(Texture const&) = delete;
	
	void LoadFromFile(const std::string &filePath);

	GLuint GetId() { return m_id; }
	void SetType(std::string type) { m_type = type; }
	const std::string& GetType() const { return m_type; }

private:
	GLuint m_id;
	std::string m_type;
	int m_width;
	int m_height;
	int m_nrChannels;
};