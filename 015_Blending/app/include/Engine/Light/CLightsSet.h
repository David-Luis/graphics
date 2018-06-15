#pragma once

#include <vector>

#include <Engine/Light/Light.h>

class DirectionalLight;
class PointLight;
class SpotLight;

class LightsSet
{
public:
	LightsSet();
	virtual ~LightsSet() {}
	LightsSet(const LightsSet&) = delete;
	LightsSet& operator=(LightsSet const&) = delete;

	void Use(const Shader& shader) const;
	void AddDirectionalLight(DirectionalLight* directionalLight);
	void AddPointLight(PointLight* pointLight);
	void AddSpotLight(SpotLight* pointLight);

	void DebugDraw(CCamera& camera);

protected:
	std::vector<Light*> m_directionalLights;
	std::vector<Light*> m_pointLights;
	std::vector<Light*> m_spotLights;

};

