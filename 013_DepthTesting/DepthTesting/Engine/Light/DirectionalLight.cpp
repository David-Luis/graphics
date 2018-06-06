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

	glm::vec3 position = m_position;
	shader.SetVec3("directionalLights[" + countStr + "].direction", position);

	glm::vec3 ambient = GetAmbient();
	shader.SetVec3("directionalLights[" + countStr + "].ambient", ambient);

	glm::vec3 diffuse = GetDiffuse();
	shader.SetVec3("directionalLights[" + countStr + "].diffuse", diffuse);

	glm::vec3 specular = GetSpecular();
	shader.SetVec3("directionalLights[" + countStr + "].specular", specular);
}

void DirectionalLight::SetDirection(const glm::vec3& position)
{
	SetPosition(position);
}

glm::vec3 DirectionalLight::GetDirection() const
{
	return GetPosition();
}