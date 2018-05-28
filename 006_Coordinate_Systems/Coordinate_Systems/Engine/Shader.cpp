#include <Engine/Shader.h>

#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader() : m_vertexShader(0), m_fragmentShader(0)
{
}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) : m_vertexShader(0), m_fragmentShader(0)
{
	m_vertexShader = LoadShader(vertexShaderPath, GL_VERTEX_SHADER);
	m_fragmentShader = LoadShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
	m_shaderProgram = LinkShaders(m_vertexShader, m_fragmentShader);
}

GLuint Shader::GetId()
{
	return m_shaderProgram;
}

void Shader::Use()
{
	glUseProgram(m_shaderProgram);
}

GLuint Shader::LoadShader(std::string shaderPath, GLenum shaderType)
{
	std::string shader = LoadShaderFile(shaderPath);
	const GLchar* const shaderChar = shader.c_str();

	GLuint vertexShader = glCreateShader(shaderType);
	glShaderSource(vertexShader, 1, &shaderChar, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		assert(false);
	}

	return vertexShader;
}

GLuint Shader::LinkShaders(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

std::string Shader::LoadShaderFile(std::string filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		assert(fileStream.is_open());
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}