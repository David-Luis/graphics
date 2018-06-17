#include <Engine/Scene/CScene.h>

#include <Engine/Model/CModel.h>
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

	for (const auto& model : m_models)
	{
		model->Update();
		model->Draw(*m_camera, *m_lightsSet);
	}

	m_lightsSet->DebugDraw(*m_camera);
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