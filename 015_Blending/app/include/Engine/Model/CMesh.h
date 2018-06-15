#pragma once

#include <Engine/Model/CMaterial.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

class CShader;
class CTexture;

struct SVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	SVertex() {}

	SVertex(float positionX, float positionY, float positionZ, float normalX, float normalY, float normalZ, float textCoordX, float textCoordY)
	{
		Position = glm::vec3(positionX, positionY, positionZ);
		Normal = glm::vec3(normalX, normalY, normalZ);
		TexCoords = glm::vec2(textCoordX, textCoordY);
	}
};

class CMesh
{
public:
	CMesh(std::vector<SVertex>& vertices, std::vector<GLuint>& indices, std::vector<CTexture*>& textures);
	virtual ~CMesh() {}
	CMesh(const CMesh&) = delete;
	CMesh& operator=(CMesh const&) = delete;

	void Draw(const CShader& shader);

	void SetMaterial(const CMaterial& material) { m_material = material; }
	void SetTextures(std::vector<CTexture*> textures) { m_textures = textures; }

private:
	void SetupMesh();

	std::vector<SVertex> m_vertices;
	std::vector<GLuint> m_indices;
	std::vector<CTexture*> m_textures;
	CMaterial m_material;

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
};
