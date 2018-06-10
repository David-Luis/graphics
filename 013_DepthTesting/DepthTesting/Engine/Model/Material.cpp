#include <Engine/Model/Material.h>

#include <Engine/Shader/Shader.h>

Material::Material() : m_ambient(1.0f, 1.0f, 1.0f), m_diffuse(1.0f, 1.0f, 1.0f), m_specular(1.0f, 1.0f, 1.0f), m_shininess(32.f)
{
	
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess)
{

}

void Material::Use(const Shader& shader)
{
	shader.SetVec3("material.ambient", GetAmbient());
	shader.SetVec3("material.diffuse", GetDiffuse());
	shader.SetVec3("material.specular", GetSpecular());
	shader.SetFloat("material.shininess", GetShininess());
}

void Material::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient;
}

glm::vec3 Material::GetAmbient() const
{
	return m_ambient;
}

void Material::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse;
}

glm::vec3 Material::GetDiffuse() const
{
	return m_diffuse;
}

void Material::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular;
}

glm::vec3 Material::GetSpecular() const
{
	return m_specular;
}

void Material::SetShininess(const float& shininess)
{
	m_shininess = shininess;
}

float Material::GetShininess() const
{
	return m_shininess;
}