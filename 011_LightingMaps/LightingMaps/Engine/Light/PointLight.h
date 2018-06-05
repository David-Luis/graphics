#pragma once

#include <Engine/Light/Light.h>

#include <glm/glm.hpp>

class Mesh;
class Shader;
class Camera;

class PointLight : public Light
{
public:
	PointLight();
	virtual ~PointLight() {}
	PointLight(const PointLight&) = delete;
	PointLight& operator=(PointLight const&) = delete;

	void DebugDraw(Camera& camera) override;

private:
	void CreateDebugDrawData();
	virtual void BindUniformsDebug(const Shader& shader, const Camera& camera);

	Mesh* m_debugMesh;
	Shader* m_debugShader;
};


