#include <Engine/Light/DirectionalLight.h>

#include <Engine/Model/Mesh.h>
#include <Engine/Shader/Shader.h>
#include <Engine/Camera/Camera.h>
#include <Engine/Utils.h>

#include <glm/gtc/type_ptr.hpp>

DirectionalLight::DirectionalLight()
{

}

void DirectionalLight::Use(const Shader& shader, int count) const
{
	std::string countStr = std::to_string(count);

	shader.SetVec3("directionalLights[" + countStr + "].direction", GetDirection());
	shader.SetVec3("directionalLights[" + countStr + "].ambient", GetAmbient());
	shader.SetVec3("directionalLights[" + countStr + "].diffuse", GetDiffuse());
	shader.SetVec3("directionalLights[" + countStr + "].specular", GetSpecular());
}

void DirectionalLight::SetDirection(const glm::vec3& position)
{
	SetPosition(position);
}

glm::vec3 DirectionalLight::GetDirection() const
{
	return GetPosition();
}