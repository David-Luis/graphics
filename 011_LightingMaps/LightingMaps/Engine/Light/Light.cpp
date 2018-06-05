#include <Engine/Light/Light.h>

#include <Engine/Shader/Shader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Light::Light() : m_ambient(0.1f, 0.1f, 0.1f), m_diffuse(0.5f, 0.5f, 0.5f), m_specular(1.0f, 1.0f, 1.0f)
{

}

void Light::Use(Shader& shader)
{
	glm::vec3 position = m_position;
	shader.SetVec3("light.position", position);

	glm::vec3 ambient = GetAmbient();
	shader.SetVec3("light.ambient", ambient);

	glm::vec3 diffuse = GetDiffuse();
	shader.SetVec3("light.diffuse", diffuse);

	glm::vec3 specular = GetSpecular();
	shader.SetVec3("light.specular", specular);
}

void Light::SetPosition(const glm::vec3& position)
{
	m_position = position;
	m_trans = glm::translate(m_trans, position);
}

glm::vec3 Light::GetPosition() const
{
	return m_position; 
}

void Light::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient; 
}

glm::vec3 Light::GetAmbient() const
{
	return m_ambient; 
}

void Light::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse; 
}

glm::vec3 Light::GetDiffuse() const
{
	return m_diffuse; 
}

void Light::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular; 
}

glm::vec3 Light::GetSpecular() const
{
	return m_specular; 
}