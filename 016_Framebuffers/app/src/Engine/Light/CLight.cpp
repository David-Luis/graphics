#include <Engine/Light/CLight.h>

#include <Engine/Shader/CShader.h>
#include <Engine/Serialization/SerializationUtils.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CLight::CLight() : m_ambient(0.1f, 0.1f, 0.1f), m_diffuse(0.5f, 0.5f, 0.5f), m_specular(1.0f, 1.0f, 1.0f)
{

}

void CLight::SetPosition(const glm::vec3& position)
{
	m_position = position;
	m_trans = glm::translate(m_trans, position);
}

glm::vec3 CLight::GetPosition() const
{
	return m_position; 
}

void CLight::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient; 
}

glm::vec3 CLight::GetAmbient() const
{
	return m_ambient; 
}

void CLight::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse; 
}

glm::vec3 CLight::GetDiffuse() const
{
	return m_diffuse; 
}

void CLight::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular; 
}

glm::vec3 CLight::GetSpecular() const
{
	return m_specular; 
}

nlohmann::json CLight::ToJson() const
{
	using json = nlohmann::json;

	json j;
	
	j["light"]["position"] = SerializationUtils::SerializeVec3(GetPosition());
	j["light"]["ambient"] = SerializationUtils::SerializeVec3(GetAmbient());
	j["light"]["diffuse"] = SerializationUtils::SerializeVec3(GetDiffuse());
	j["light"]["specular"] = SerializationUtils::SerializeVec3(GetSpecular());

	return j;
}

void CLight::FromJson(const nlohmann::json& j)
{
	SetPosition(SerializationUtils::DeserializeVec3(j["light"]["position"]));
	SetAmbient(SerializationUtils::DeserializeVec3(j["light"]["ambient"]));
	SetDiffuse(SerializationUtils::DeserializeVec3(j["light"]["diffuse"]));
	SetSpecular(SerializationUtils::DeserializeVec3(j["light"]["specular"]));
}