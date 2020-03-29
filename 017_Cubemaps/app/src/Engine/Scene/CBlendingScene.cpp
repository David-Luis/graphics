#include <Engine/Scene/CBlendingScene.h>

#include <Engine/Camera/CCamera.h>
#include <Engine/Model/CModel.h>

#include <glm/glm.hpp>

#include <algorithm>

std::vector<CModel*> CBlendingScene::GetModelsForDraw()
{
	std::vector<CModel*> models = m_models;

	sort(models.begin(), models.end(),
		[this](const CModel* model, const CModel* other) -> bool
	{
		float distanceModel = glm::distance(m_camera->GetPosition(), model->GetPosition());
		float distanceOther = glm::distance(m_camera->GetPosition(), other->GetPosition());
		return distanceModel >= distanceOther;
	});

	return models;
}
