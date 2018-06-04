#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

class Shader;
class Texture;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	Vertex() {}

	Vertex(float positionX, float positionY, float positionZ, float normalX, float normalY, float normalZ, float textCoordX, float textCoordY)
	{
		Position = glm::vec3(positionX, positionY, positionZ);
		Normal = glm::vec3(normalX, normalY, normalZ);
		TexCoords = glm::vec2(textCoordX, textCoordY);
	}
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture*>& textures);
	virtual ~Mesh() {}
	Mesh(const Mesh&) = delete;
	Mesh& operator=(Mesh const&) = delete;

	void Draw(const Shader& shader);

private:
	void SetupMesh();

	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	std::vector<Texture*> m_textures;

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
};
