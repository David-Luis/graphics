#pragma once

#include <Engine/Scene/CScene.h>

#include <vector>

class CModel;

class CBlendingScene : public CScene
{
protected:
	std::vector<CModel*> GetModelsForDraw() override;
};

