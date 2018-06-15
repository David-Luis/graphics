#pragma once

#include <glm/glm.hpp>

class Shader;
class CCamera;

class Light
{
public:
	Light();
	virtual ~Light() {}
	Light(const Light&) = delete;
	Light& operator=(Light const&) = delete;

	virtual void Use(const Shader& shader, int count) const = 0;
	virtual void DebugDraw(CCamera& camera) = 0;

	void SetPosition(const glm::vec3& position);
	glm::vec3 GetPosition() const;

	void SetAmbient(const glm::vec3& ambient);
	glm::vec3 GetAmbient() const;

	void SetDiffuse(const glm::vec3& diffuse);
	glm::vec3 GetDiffuse() const;

	void SetSpecular(const glm::vec3& specular);
	glm::vec3 GetSpecular() const;

protected:
	glm::mat4 m_trans;

	glm::vec3 m_position;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

