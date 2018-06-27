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

nlohmann::json CLightsSet::ToJson() const
{
	using json = nlohmann::json;

	json lightsJson;

	std::vector<json> directionLightsJson;
	for (const auto& directionalLight : m_directionalLights)
	{
		directionLightsJson.push_back(directionalLight->ToJson());
	}

	std::vector<json> pointLightsJson;
	for (const auto& pointLight : m_pointLights)
	{
		pointLightsJson.push_back(pointLight->ToJson());
	}

	std::vector<json> spotLightsJson;
	for (const auto& spotLight : m_spotLights)
	{
		spotLightsJson.push_back(spotLight->ToJson());
	}

	lightsJson["directionalLights"] = directionLightsJson;
	lightsJson["pointLights"] = pointLightsJson;
	lightsJson["spotLights"] = spotLightsJson;

	return lightsJson;
}

void CLightsSet::FromJson(const nlohmann::json& j)
{
	using json = nlohmann::json;
	json directionalLights = j["directionalLights"];
	json pointLights = j["pointLights"];
	json spotLights = j["spotLights"];

	if (!directionalLights.empty())
	{
		for (auto& node : directionalLights)
		{
			CDirectionalLight* light = new CDirectionalLight();
			light->FromJson(node);
			AddDirectionalLight(light);
		}
	}

	if (!pointLights.empty())
	{
		for (auto& node : pointLights)
		{
			CPointLight* light = new CPointLight();
			light->FromJson(node);
			AddPointLight(light);
		}
	}

	if (!spotLights.empty())
	{
		for (auto& node : spotLights)
		{
			CSpotLight* light = new CSpotLight();
			light->FromJson(node);
			AddSpotLight(light);
		}
	}
}

void CLightsSet::Clear()
{
	m_directionalLights.clear();
	m_pointLights.clear();
	m_directionalLights.clear();
}