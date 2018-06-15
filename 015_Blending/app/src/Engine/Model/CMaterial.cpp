#include <Engine/Model/CMaterial.h>

#include <Engine/Shader/CShader.h>

CMaterial::CMaterial() : m_ambient(1.0f, 1.0f, 1.0f), m_diffuse(1.0f, 1.0f, 1.0f), m_specular(1.0f, 1.0f, 1.0f), m_shininess(32.f)
{
	
}

CMaterial::CMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess)
{

}

void CMaterial::Use(const CShader& shader)
{
	shader.SetVec3("material.ambient", GetAmbient());
	shader.SetVec3("material.diffuse", GetDiffuse());
	shader.SetVec3("material.specular", GetSpecular());
	shader.SetFloat("material.shininess", GetShininess());
}

void CMaterial::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient;
}

glm::vec3 CMaterial::GetAmbient() const
{
	return m_ambient;
}

void CMaterial::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse;
}

glm::vec3 CMaterial::GetDiffuse() const
{
	return m_diffuse;
}

void CMaterial::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular;
}

glm::vec3 CMaterial::GetSpecular() const
{
	return m_specular;
}

void CMaterial::SetShininess(const float& shininess)
{
	m_shininess = shininess;
}

float CMaterial::GetShininess() const
{
	return m_shininess;
}