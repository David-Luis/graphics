#pragma once

#include <Engine/Light/Light.h>

#include <glm/glm.hpp>

class Mesh;
class Shader;
class CCamera;

class PointLight : public Light
{
public:
	PointLight();
	virtual ~PointLight() {}
	PointLight(const PointLight&) = delete;
	PointLight& operator=(PointLight const&) = delete;

	void SetAttenuation(float constant, float linear, float quadratic);

	void DebugDraw(CCamera& camera) override;

private:
	void Use(const Shader& shader, int count) const override;
	void BindUniformsDebug(const Shader& shader, const CCamera& camera);

	void CreateDebugDrawData();

	Mesh* m_debugMesh;
	Shader* m_debugShader;

	float m_constantAttenuation;
	float m_linearAttenuation;
	float m_quadraticAttenuation;
};


