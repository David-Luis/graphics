#include "Model.h"

#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

Model::Model() : m_shader(nullptr), m_texture(nullptr), m_mesh(nullptr)
{

}

Model::Model(Shader* shader, Texture* texture, Mesh* mesh) : m_shader(shader), m_texture(texture), m_mesh(mesh)
{

}

void Model::Draw()
{
	if (m_shader)
	{
		m_shader->Use();
	}
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