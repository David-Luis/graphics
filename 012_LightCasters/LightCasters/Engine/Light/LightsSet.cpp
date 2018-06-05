#include <Engine/Light/LightsSet.h>

#include <Engine/Light/DirectionalLight.h>
#include <Engine/Light/PointLight.h>
#include <Engine/Shader/Shader.h>

LightsSet::LightsSet()
{

}

void LightsSet::Use(const Shader& shader) const
{
	shader.SetInt("numDirectionalLights", m_directionalLights.size());
	shader.SetInt("numPointLights", m_pointLights.size());

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
}

void LightsSet::AddPointLight(PointLight* pointLight)
{
	m_pointLights.push_back(pointLight);
}

void LightsSet::AddDirectionalLight(DirectionalLight* directionalLight)
{
	m_directionalLights.push_back(directionalLight);
}

void LightsSet::DebugDraw(Camera& camera)
{
	for (const auto& directionalLight : m_directionalLights)
	{
		directionalLight->DebugDraw(camera);
	}

	for (const auto& pointLight : m_pointLights)
	{
		pointLight->DebugDraw(camera);
	}
}