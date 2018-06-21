#pragma once

#include <Engine/Light/CLight.h>

#include <glm/glm.hpp>

class CMesh;
class CShader;
class CCCamera;

class CDirectionalLight : public CLight
{
public:
	CDirectionalLight();
	virtual ~CDirectionalLight() {}
	CDirectionalLight(const CDirectionalLight&) = delete;
	CDirectionalLight& operator=(CDirectionalLight const&) = delete;

	void SetDirection(const glm::vec3& position);
	glm::vec3 GetDirection() const;

	void DebugDraw(CCamera& camera) override {}

private:
	void Use(const CShader& shader, int count) const override;
};


