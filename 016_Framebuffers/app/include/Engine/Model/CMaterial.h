#pragma once

#include <glm/glm.hpp>

class CShader;

class CMaterial
{
public:
	CMaterial();
	CMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

	virtual ~CMaterial() {}

	void Use(const CShader& shader) const;

	void SetAmbient(const glm::vec3& ambient);
	glm::vec3 GetAmbient() const;

	void SetDiffuse(const glm::vec3& diffuse);
	glm::vec3 GetDiffuse() const;

	void SetSpecular(const glm::vec3& specular);
	glm::vec3 GetSpecular() const;

	void SetShininess(const float& shininess);
	float GetShininess() const;

private:
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_shininess;
};
