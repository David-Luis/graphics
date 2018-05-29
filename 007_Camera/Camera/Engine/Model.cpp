#include <Engine/Model.h>

#include <Engine/Texture.h>
#include <Engine/Mesh.h>
#include <Engine/Shader.h>
#include <Engine/Camera.h>

Model::Model() : m_shader(nullptr), m_texture(nullptr), m_mesh(nullptr)
{

}

Model::Model(Shader* shader, Texture* texture, Mesh* mesh) : m_shader(shader), m_texture(texture), m_mesh(mesh)
{

}

void Model::Draw(Camera* m_camera)
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
	
	BindUniforms(m_camera);
	glDrawElements(GL_TRIANGLES, m_mesh->VertexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Model::BindUniforms(Camera* m_camera)
{
	if (m_shader)
	{
		unsigned int transformLoc = glGetUniformLocation(m_shader->GetId(), "model");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(m_trans));

		unsigned int viewLoc = glGetUniformLocation(m_shader->GetId(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera->GetViewMatrix()));

		unsigned int projecttionLoc = glGetUniformLocation(m_shader->GetId(), "projection");
		glUniformMatrix4fv(projecttionLoc, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjectionMatrix()));
	}
}