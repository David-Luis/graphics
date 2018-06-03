#include <Engine/Model.h>

#include <Engine/Texture.h>
#include <Engine/Mesh.h>
#include <Engine/Shader.h>
#include <Engine/Camera.h>
#include <Engine/Engine.h>
#include <Engine/AssetsManager.h>

#include <iostream>

Model::Model() : m_color(1.0f, 1.0f, 1.0f)
{

}

Model::Model(std::vector<Mesh*>& meshes) : m_color(1.0f, 1.0f, 1.0f)
{
	m_meshes = meshes;
}

Model::~Model()
{
	for (size_t i = 0; i < m_meshes.size(); i++)
		delete m_meshes[i];

	m_meshes.clear();
}

void Model::Draw(Shader& shader, Camera& m_camera)
{
	shader.Use();
	BindUniforms(shader, m_camera);
	
	for (size_t i = 0; i < m_meshes.size(); i++)
		m_meshes[i]->Draw(shader);
}

void Model::BindUniforms(const Shader& shader, const Camera& camera)
{
	GLuint transformLoc = glGetUniformLocation(shader.GetId(), "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(m_trans));

	GLuint viewLoc = glGetUniformLocation(shader.GetId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

	GLuint projecttionLoc = glGetUniformLocation(shader.GetId(), "projection");
	glUniformMatrix4fv(projecttionLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjectionMatrix()));

	glm::vec3 viewPos = camera.GetPosition();
	shader.setVec3("viewPos", viewPos);

	glm::vec3 color = GetColor();
	shader.setVec3("objectColor", color);
}