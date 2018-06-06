#pragma once

#include <Engine/Light/Light.h>

#include <glm/glm.hpp>

class Mesh;
class Shader;
class Camera;

class SpotLight : public Light
{
public:
	SpotLight();
	virtual ~SpotLight() {}
	SpotLight(const SpotLight&) = delete;
	SpotLight& operator=(SpotLight const&) = delete;

	void SetAttenuation(float constant, float linear, float quadratic);
	void SetCutoff(float cutOff, float outerCutOff);

	void SetDirection(const glm::vec3& direction);
	glm::vec3 GetDirection() const;

	void DebugDraw(Camera& camera) override;

private:
	void Use(const Shader& shader, int count) const override;
	void BindUniformsDebug(const Shader& shader, const Camera& camera);

	void CreateDebugDrawData();

	Mesh* m_debugMesh;
	Shader* m_debugShader;

	glm::vec3 m_direction;

	float m_constantAttenuation;
	float m_linearAttenuation;
	float m_quadraticAttenuation;

	float m_cutOff;
	float m_outerCutOff;
};


