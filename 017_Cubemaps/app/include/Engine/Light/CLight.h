#pragma once

#include <glm/glm.hpp>

#include <Lib/json.hpp>

class CShader;
class CCamera;

class CLight
{
public:
	CLight();
	virtual ~CLight() {}
	CLight(const CLight&) = delete;
	CLight& operator=(CLight const&) = delete;

	virtual void Use(const CShader& shader, int count) const = 0;
	virtual void DebugDraw(CCamera& camera) = 0;

	void SetPosition(const glm::vec3& position);
	glm::vec3 GetPosition() const;

	void SetAmbient(const glm::vec3& ambient);
	glm::vec3 GetAmbient() const;

	void SetDiffuse(const glm::vec3& diffuse);
	glm::vec3 GetDiffuse() const;

	void SetSpecular(const glm::vec3& specular);
	glm::vec3 GetSpecular() const;

	virtual nlohmann::json ToJson() const;
	virtual void FromJson(const nlohmann::json&);

protected:
	glm::mat4 m_trans;

	glm::vec3 m_position;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

