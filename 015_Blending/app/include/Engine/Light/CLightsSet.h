#pragma once

#include <vector>

#include <Engine/Light/CLight.h>

class CDirectionalLight;
class CPointLight;
class CSpotLight;

class CLightsSet
{
public:
	CLightsSet();
	virtual ~CLightsSet() {}
	CLightsSet(const CLightsSet&) = delete;
	CLightsSet& operator=(CLightsSet const&) = delete;

	void Use(const CShader& shader) const;
	void AddDirectionalLight(CDirectionalLight* directionalLight);
	void AddPointLight(CPointLight* pointLight);
	void AddSpotLight(CSpotLight* pointLight);

	void DebugDraw(CCamera& camera);

protected:
	std::vector<CLight*> m_directionalLights;
	std::vector<CLight*> m_pointLights;
	std::vector<CLight*> m_spotLights;

};

