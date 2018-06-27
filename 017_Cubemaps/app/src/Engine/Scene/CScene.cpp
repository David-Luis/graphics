#include <Engine/Scene/CScene.h>

#include <Engine/Model/CModel.h>
#include <Engine/Model/CModelFactory.h>
#include <Engine/Light/CLightsSet.h>
#include <Engine/Camera/CCamera.h>

#include <assert.h>

std::ostream &operator<<(std::ostream& stream, const CScene& scene)
{
	using json = nlohmann::json;
	json j = scene.ToJson();

	stream << j.dump(4);

	return stream;
}

std::istream &operator>>(std::istream &stream, CScene& scene)
{
	using json = nlohmann::json;

	std::string str(std::istreambuf_iterator<char>(stream), {}); 
	json j = json::parse(str);

	scene.FromJson(j);

	return stream;
}

CScene::CScene() : m_lightsSet(nullptr)
{

}

CScene::~CScene()
{

}

void CScene::Draw()
{
	assert(m_camera);
	//assert(m_lightsSet);

	auto models = GetModelsForDraw();
	for (const auto& model : models)
	{
		model->Update();
		model->Draw(*m_camera, *m_lightsSet);
	}

	if (m_lightsSet)
	{
		m_lightsSet->DebugDraw(*m_camera);
	}
}

void CScene::Clear() 
{
	m_models.clear(); 
	if (m_lightsSet)
	{
		m_lightsSet->Clear();
	}
}

nlohmann::json CScene::ToJson() const
{
	using json = nlohmann::json;
	json outputJson;

	std::vector<json> modelsJson;
	json cameraJson;
	json lightSetJson;

	cameraJson = m_camera->ToJson();
	lightSetJson = m_lightsSet->ToJson();
	for (const auto& model : m_models)
	{
		modelsJson.push_back(model->ToJson());
	}

	outputJson["camera"] = cameraJson;
	outputJson["lights"] = lightSetJson;
	outputJson["models"] = modelsJson;

	return outputJson;
}

void CScene::FromJson(const nlohmann::json& j)
{
	using json = nlohmann::json;

	json cameraJson = j["camera"];
	json lightsJson = j["lights"];
	json modelsJson = j["models"];

	m_camera->FromJson(cameraJson);

	if (!m_lightsSet)
	{
		m_lightsSet = new CLightsSet();
	}
	m_lightsSet->FromJson(lightsJson);

	if (!modelsJson.empty())
	{
		for (auto& node : modelsJson)
		{
			CModel* model = CModelFactory::CreateModelFromJson(node);
			AddModel(model);
			model->FromJson(node);
		}
	}
}

std::vector<CModel*> CScene::GetModelsForDraw()
{
	return m_models;
}