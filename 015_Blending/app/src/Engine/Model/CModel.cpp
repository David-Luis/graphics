#include <Engine/Model/CModel.h>

#include <Engine/Texture/CTexture.h>
#include <Engine/Model/CMesh.h>
#include <Engine/Shader/CShader.h>
#include <Engine/Camera/CCamera.h>
#include <Engine/Engine.h>
#include <Engine/Light/CLightsSet.h>
#include <Engine/Serialization/SerializationUtils.h>

#include <iostream>

std::ostream &operator<<(std::ostream& stream, const CModel& model)
{
	using json = nlohmann::json;
	json j = model.ToJson();

	stream << j.dump(4);

	return stream;
}

CModel::CModel() 
	: m_translation(0.f, 0.f, 0.f)
	, m_rotation()
	, m_scale(1.f, 1.f, 1.f)
{
	CalculateTransformation();
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

void CModel::SetTranslation(glm::vec3 translation)
{
	m_translation = translation;
	CalculateTransformation();
}

void CModel::Translate(glm::vec3 translation)
{
	m_translation += translation;
	CalculateTransformation();
}

void CModel::SetRotation(glm::quat rotation)
{
	m_rotation = glm::toMat4(rotation);
	CalculateTransformation();
}

void CModel::SetRotation(float angle, glm::vec3 axis)
{
	m_rotation = glm::toMat4(glm::angleAxis(angle, axis));
	CalculateTransformation();
}

void CModel::Rotate(glm::quat rotation)
{
	//check maths here
	m_rotation = m_rotation * glm::toMat4(rotation);
	CalculateTransformation();
}

void CModel::Rotate(float angle, glm::vec3 axis)
{
	m_rotation = glm::rotate(m_rotation, angle, axis);

	CalculateTransformation();
}

void CModel::SetScale(glm::vec3 scale)
{
	m_scale = scale;
	CalculateTransformation();
}

void CModel::Scale(glm::vec3 scale)
{
	m_scale *= scale;
	CalculateTransformation();
}

void CModel::CalculateTransformation()
{
	m_transform = glm::mat4();

	m_transform = glm::translate(m_transform, m_translation);
	m_transform = m_transform * m_rotation;
	m_transform = glm::scale(m_transform, m_scale);
}

void CModel::BindUniforms()
{
	m_shader->SetMat4("model", std::move(m_transform));
}

nlohmann::json CModel::ToJson() const
{
	using json = nlohmann::json;

	json j;

	j["model"]["translation"] = SerializationUtils::SerializeVec3(m_translation);
	j["model"]["rotation"] = SerializationUtils::SerializeMat4(m_rotation);
	j["model"]["scale"] = SerializationUtils::SerializeVec3(m_scale);

	return j;
}

void CModel::FromJson(nlohmann::json j)
{
	SetTranslation(SerializationUtils::DeserializeVec3(j["model"]["translation"]));
	SetRotation(SerializationUtils::DeserializeMat4(j["model"]["rotation"]));
	SetScale(SerializationUtils::DeserializeVec3(j["model"]["scale"]));
}
