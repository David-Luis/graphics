#include <Engine/Model/CModel.h>

#include <Engine/Texture/CTexture.h>
#include <Engine/Model/CMesh.h>
#include <Engine/Shader/CShader.h>
#include <Engine/Camera/CCamera.h>
#include <Engine/Engine.h>
#include <Engine/Light/CLightsSet.h>

#include <iostream>

CModel::CModel()
{

}

CModel::CModel(std::vector<CMesh*>& meshes) 
{
	m_meshes = meshes;
}

CModel::~CModel()
{
	for (size_t i = 0; i < m_meshes.size(); i++)
		delete m_meshes[i];

	m_meshes.clear();
}

void CModel::Draw(CCamera& m_camera, CLightsSet& lights)
{
	assert(m_shader);

	m_shader->Use();
	BindUniforms();
	m_camera.Use(*m_shader);
	lights.Use(*m_shader);

	for (const auto& mesh : m_meshes)
	{
		mesh->Draw(*m_shader);
	}
}

void CModel::BindUniforms()
{
	m_shader->SetMat4("model", std::move(m_trans));
}

void CModel::SetTransformComponents(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float angle)
{
	glm::mat4 trans;
	trans = glm::translate(trans, position);
	trans = glm::scale(trans, scale);
	trans = glm::rotate(trans, angle, rotation);
	SetTransform(trans);
}