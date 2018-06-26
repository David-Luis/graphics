#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class CShader
{
public:
	CShader();
	CShader(std::string vertexShaderPath, std::string fragmentShaderPath);
	virtual ~CShader() {}
	CShader(const CShader&) = delete;
	CShader& operator=(CShader const&) = delete;

	GLuint GetId() const { return m_shaderProgram; }
	void Use();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, glm::vec3&& value) const;
	void SetVec4(const std::string& name, glm::vec4&& value) const;
	void SetVec4i(const std::string& name, glm::ivec4&& value) const;
	void SetMat4(const std::string& name, glm::mat4&& value) const;

private:
	GLuint LoadShader(std::string shaderPath, GLenum shaderType);
	GLuint LinkShaders(GLuint vertexShader, GLuint fragmentShader);
	std::string LoadShaderFile(std::string filePath);

	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;
};


