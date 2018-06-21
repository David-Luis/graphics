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

CScene::CScene()
{

}

CScene::~CScene()
{

}

void CScene::Draw()
{
	assert(m_camera);
	assert(m_lightsSet);

	auto models = GetModelsForDraw();
	for (const auto& model : models)
	{
		model->Update();
		model->Draw(*m_camera, *m_lightsSet);
	}

	m_lightsSet->DebugDraw(*m_camera);
}

void CScene::Clear() 
{
	m_models.clear(); 

	//TODO: Remove also lights and set camera to null
}

nlohmann::json CScene::ToJson() const
{
	using json = nlohmann::json;
	json j;

	std::vector<json> models;

	for (const auto& model : m_models)
	{
		models.push_back(model->ToJson());
	}
	j["models"] = models;

	return j;
}

void CScene::FromJson(nlohmann::json j)
{
	if (!j["models"].empty())
	{
		for (auto& node : j["models"])
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