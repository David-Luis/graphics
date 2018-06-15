#pragma once

#include <Engine/Light/CLight.h>

#include <glm/glm.hpp>

class CMesh;
class CShader;
class CCamera;

class CPointLight : public CLight
{
public:
	CPointLight();
	virtual ~CPointLight() {}
	CPointLight(const CPointLight&) = delete;
	CPointLight& operator=(CPointLight const&) = delete;

	void SetAttenuation(float constant, float linear, float quadratic);

	void DebugDraw(CCamera& camera) override;

private:
	void Use(const CShader& shader, int count) const override;
	void BindUniformsDebug(const CShader& shader, const CCamera& camera);

	void CreateDebugDrawData();

	CMesh* m_debugMesh;
	CShader* m_debugShader;

	float m_constantAttenuation;
	float m_linearAttenuation;
	float m_quadraticAttenuation;
};


