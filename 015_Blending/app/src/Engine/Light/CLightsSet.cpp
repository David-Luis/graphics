#include <Engine/Light/CLightsSet.h>

#include <Engine/Light/CDirectionalLight.h>
#include <Engine/Light/CPointLight.h>
#include <Engine/Light/CSpotLight.h>
#include <Engine/Shader/CShader.h>

CLightsSet::CLightsSet()
{

}

void CLightsSet::Use(const CShader& shader) const
{
	shader.SetInt("numDirectionalLights", m_directionalLights.size());
	shader.SetInt("numPointLights", m_pointLights.size());
	shader.SetInt("numSpotLights", m_spotLights.size());

	int directionalLightsCount = 0;
	for (const auto& directionalLight : m_directionalLights)
	{
		directionalLight->Use(shader, directionalLightsCount);
		directionalLightsCount++;
	}

	int pointLightsCount = 0;
	for (const auto& pointLight : m_pointLights)
	{
		pointLight->Use(shader, pointLightsCount);
		pointLightsCount++;
	}

	int spotLightsCount = 0;
	for (const auto& spotLight : m_spotLights)
	{
		spotLight->Use(shader, spotLightsCount);
		spotLightsCount++;
	}
}

void CLightsSet::AddDirectionalLight(CDirectionalLight* directionalLight)
{
	m_directionalLights.push_back(directionalLight);
}

void CLightsSet::AddPointLight(CPointLight* pointLight)
{
	m_pointLights.push_back(pointLight);
}

void CLightsSet::AddSpotLight(CSpotLight* spotLight)
{
	m_spotLights.push_back(spotLight);
}

void CLightsSet::DebugDraw(CCamera& camera)
{
	for (const auto& directionalLight : m_directionalLights)
	{
		directionalLight->DebugDraw(camera);
	}

	for (const auto& pointLight : m_pointLights)
	{
		pointLight->DebugDraw(camera);
	}

	for (const auto& spotLight : m_spotLights)
	{
		spotLight->DebugDraw(camera);
	}
}