#include <Engine/Light/CDirectionalLight.h>

#include <Engine/Model/CMesh.h>
#include <Engine/Shader/CShader.h>
#include <Engine/Camera/CCamera.h>
#include <Engine/Utils.h>

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