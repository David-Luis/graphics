#pragma once

#include <glad/glad.h>

#include <string>

class CShader;

class CTexture {

public:
	CTexture() {}
	CTexture(const CTexture&) = delete;
	CTexture& operator=(CTexture const&) = delete;
	
	virtual void LoadFromFile(const std::string &filePath);
	virtual void Use(const CShader& shader, GLuint index) const;

	void SetId(GLuint id) { m_id = id; }
	GLuint GetId() const { return m_id; }
	void SetType(std::string type) { m_type = type; }
	const std::string& GetType() const { return m_type; }

protected:
	GLuint m_id;
	std::string m_type;
	int m_width;
	int m_height;
	int m_nrChannels;
};