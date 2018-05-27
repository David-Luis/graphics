#pragma once

#include <glad/glad.h>

#include <vector>

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<float>& vertices, std::vector<GLuint>& indices);

	void Use();

private:
	std::vector<float> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
};
