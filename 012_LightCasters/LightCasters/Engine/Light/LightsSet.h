#pragma once

#include <vector>

#include <Engine/Light/Light.h>

class PointLight;
class DirectionalLight;

class LightsSet
{
public:
	LightsSet();
	virtual ~LightsSet() {}
	LightsSet(const LightsSet&) = delete;
	LightsSet& operator=(LightsSet const&) = delete;

	void Use(const Shader& shader) const;
	void AddPointLight(PointLight* pointLight);
	void AddDirectionalLight(DirectionalLight* directionalLight);

	void DebugDraw(Camera& camera);

protected:
	std::vector<Light*> m_pointLights;
	std::vector<Light*> m_directionalLights;

};

