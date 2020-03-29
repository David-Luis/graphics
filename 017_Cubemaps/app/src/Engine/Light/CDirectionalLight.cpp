#include <Engine/Light/CDirectionalLight.h>

#include <Engine/Model/CMesh.h>
#include <Engine/Shader/CShader.h>
#include <Engine/Camera/CCamera.h>
#include <Engine/Utils.h>
#include <Engine/Serialization/SerializationUtils.h>

#include <glm/gtc/type_ptr.hpp>

CDirectionalLight::CDirectionalLight()
{

}

void CDirectionalLight::Use(const CShader& shader, int count) const
{
	std::string countStr = std::to_string(count);

	shader.SetVec3("directionalLights[" + countStr + "].direction", GetDirection());
	shader.SetVec3("directionalLights[" + countStr + "].ambient", GetAmbient());
	shader.SetVec3("directionalLights[" + countStr + "].diffuse", GetDiffuse());
	shader.SetVec3("directionalLights[" + countStr + "].specular", GetSpecular());
}

void CDirectionalLight::SetDirection(const glm::vec3& position)
{
	SetPosition(position);
}

glm::vec3 CDirectionalLight::GetDirection() const
{
	return GetPosition();
}

nlohmann::json CDirectionalLight::ToJson() const
{
	using json = nlohmann::json;

	json j;

	j = CLight::ToJson();
	
	return j;
}

void CDirectionalLight::FromJson(const nlohmann::json& j)
{
	CLight::FromJson(j);
	SetDirection(SerializationUtils::DeserializeVec3(j["light"]["position"]));
}
