#include <Engine/Model/CMesh.h>
#include <Engine/Texture/CTexture.h>
#include <Engine/Shader/CShader.h>

CMesh::CMesh(std::vector<SVertex>& vertices, std::vector<GLuint>& indices, std::vector<CTexture*>& textures) : m_vertices(vertices), m_indices(indices), m_textures(textures), m_VAO(0), m_VBO(0), m_EBO(0)
{
	SetupMesh();
}

void CMesh::Draw(const CShader& shader)
{
	m_material.Use(shader);

	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (size_t i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
										  // retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = m_textures[i]->GetType();
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		name = "material." + name + "_" + number;
		shader.SetInt(name, static_cast<int>(i));
		glBindTexture(GL_TEXTURE_2D, m_textures[i]->GetId());
	}

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void CMesh::SetupMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, TexCoords));

	glBindVertexArray(0);
}