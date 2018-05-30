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

	GLuint GetId() const { return m_shaderProgram; }
	void Use();
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;

private:
	GLuint LoadShader(std::string shaderPath, GLenum shaderType);
	GLuint LinkShaders(GLuint vertexShader, GLuint fragmentShader);
	std::string LoadShaderFile(std::string filePath);

	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;
};


