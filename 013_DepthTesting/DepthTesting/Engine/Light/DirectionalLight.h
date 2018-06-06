#pragma once

#include <Engine/Light/Light.h>

#include <glm/glm.hpp>

class Mesh;
class Shader;
class Camera;

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	virtual ~DirectionalLight() {}
	DirectionalLight(const DirectionalLight&) = delete;
	DirectionalLight& operator=(DirectionalLight const&) = delete;

	void SetDirection(const glm::vec3& position);
	glm::vec3 GetDirection() const;

	void DebugDraw(Camera& camera) override {}

private:
	void Use(const Shader& shader, int count) const override;
};


