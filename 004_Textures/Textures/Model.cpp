#include "Model.h"

#include "Texture.h"
#include "Mesh.h"

Model::Model() : m_shaderProgram(0), m_texture(nullptr), m_mesh(nullptr)
{

}

Model::Model(GLuint shaderProgram, Texture* texture, Mesh* mesh) : m_shaderProgram(shaderProgram), m_texture(texture), m_mesh(mesh)
{

}

void Model::Draw()
{
	glUseProgram(m_shaderProgram);
	if (m_texture)
	{
		m_texture->Use();
	}
	if (m_mesh)
	{
		m_mesh->Use();
	}
	BindUniforms();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}