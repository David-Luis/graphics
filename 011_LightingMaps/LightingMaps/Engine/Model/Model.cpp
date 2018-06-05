#include <Engine/Model/Model.h>

#include <Engine/Texture/Texture.h>
#include <Engine/Model/Mesh.h>
#include <Engine/Shader/Shader.h>
#include <Engine/Camera/Camera.h>
#include <Engine/Engine.h>
#include <Engine/Light/Light.h>

#include <iostream>

Model::Model()
{

}

Model::Model(std::vector<Mesh*>& meshes) 
{
	m_meshes = meshes;
}

Model::~Model()
{
	for (size_t i = 0; i < m_meshes.size(); i++)
		delete m_meshes[i];

	m_meshes.clear();
}

void Model::Draw(Shader& shader, Camera& m_camera, std::vector<Light*> lights)
{
	shader.Use();
	BindUniforms(shader);
	m_camera.Use(shader);
	for (const auto& light : lights)
	{
		light->Use(shader);
	}

	for (const auto& mesh : m_meshes)
	{
		mesh->Draw(shader);
	}
}

void Model::BindUniforms(const Shader& shader)
{
	glm::mat4 model = m_trans;
	shader.SetMat4("model", model);
}