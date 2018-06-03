#pragma once

#include <glm/glm.hpp>

class Mesh;
class Shader;
class Camera;

class PointLight
{
public:
	PointLight();
	virtual ~PointLight() {}
	PointLight(const PointLight&) = delete;
	PointLight& operator=(PointLight const&) = delete;

	void Use(Shader& shader);

	void DebugDraw(Camera& camera);

	void SetTransform(const glm::mat4& trans) { m_trans = trans; }
	glm::mat4 GetTransform() { return m_trans; }

	void SetColor(const glm::vec3& color) { m_color = color; }
	glm::vec3 GetColor() { return m_color; }

private:
	virtual void BindUniformsDebug(const Shader& shader, const Camera& camera);

	Mesh* m_debugMesh;
	Shader* m_debugShader;

	glm::mat4 m_trans;
	glm::vec3 m_color;
};


