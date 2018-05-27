#pragma once

#include <glad/glad.h>

#include <string>

class Shader
{
public:
	Shader();
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	virtual ~Shader() {}
	Shader(const Shader&) = delete;
	Shader& operator=(Shader const&) = delete;

	void Use();

private:
	GLuint LoadShader(std::string shaderPath, GLenum shaderType);
	GLuint LinkShaders(GLuint vertexShader, GLuint fragmentShader);
	std::string LoadShaderFile(std::string filePath);

	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;
};


