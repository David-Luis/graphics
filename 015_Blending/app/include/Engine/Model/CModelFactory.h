#pragma once

#include <Lib/json.hpp>

#include <glm/glm.hpp>

class CModel;

class CModelFactory
{
public:
	static CModel* CreateModel();
	static CModel* CreateModelFromJson(nlohmann::json j);
};
