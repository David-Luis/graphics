#include <Engine/Light/CLight.h>

#include <Engine/Shader/CShader.h>

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