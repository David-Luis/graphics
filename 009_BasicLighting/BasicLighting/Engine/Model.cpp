#include <Engine/Model.h>

#include <Engine/Texture.h>
#include <Engine/Mesh.h>
#include <Engine/Shader.h>
#include <Engine/Camera.h>
#include <Engine/Engine.h>
#include <Engine/AssetsManager.h>
#include <Engine/Light/PointLight.h>

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

void Model::Draw(Shader& shader, Camera& m_camera, std::vector<PointLight*> lights)
{
	shader.Use();
	BindUniforms(shader);
	m_camera.Use(shader);
	for (const auto& light : lights)
	{
		light->Use(shader);
	}
	
	for (size_t i = 0; i < m_meshes.size(); i++)
		m_meshes[i]->Draw(shader);
}

void Model::BindUniforms(const Shader& shader)
{
	glm::mat4 model = m_trans;
	shader.SetMat4("model", model);

	glm::vec3 color = GetColor();
	shader.SetVec3("objectColor", color);
}