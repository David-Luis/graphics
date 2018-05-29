#pragma once

#include <glad/glad.h>

#include <vector>

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<float>& vertices, std::vector<GLuint>& indices);
	virtual ~Mesh() {}
	Mesh(const Mesh&) = delete;
	Mesh& operator=(Mesh const&) = delete;

	void Use();
	int VertexCount();

private:
	std::vector<float> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
};
