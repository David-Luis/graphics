#pragma once

#include <Engine/Light/CLight.h>

#include <glm/glm.hpp>

class CMesh;
class CShader;
class CCamera;

class CSpotLight : public CLight
{
public:
	CSpotLight();
	virtual ~CSpotLight() {}
	CSpotLight(const CSpotLight&) = delete;
	CSpotLight& operator=(CSpotLight const&) = delete;

	void SetAttenuation(float constant, float linear, float quadratic);
	void SetCutoff(float cutOff, float outerCutOff);

	void SetDirection(const glm::vec3& direction);
	glm::vec3 GetDirection() const;

	void DebugDraw(CCamera& camera) override;

private:
	void Use(const CShader& shader, int count) const override;
	void BindUniformsDebug(const CShader& shader, const CCamera& camera);

	void CreateDebugDrawData();

	CMesh* m_debugMesh;
	CShader* m_debugShader;

	glm::vec3 m_direction;

	float m_constantAttenuation;
	float m_linearAttenuation;
	float m_quadraticAttenuation;

	float m_cutOff;
	float m_outerCutOff;
};


