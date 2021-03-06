#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class CTexture {

public:
	CTexture() {}
	CTexture(const CTexture&) = delete;
	CTexture& operator=(CTexture const&) = delete;
	
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