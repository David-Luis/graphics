#include <Engine/Model/CModelFactory.h>

#include <Engine/Model/CAssimpModel.h>

CModel* CModelFactory::CreateModel()
{
	CAssimpModel* model = new CAssimpModel();

	return model;
}

CModel* CModelFactory::CreateModelFromJson(nlohmann::json j)
{
	CAssimpModel* model = new CAssimpModel();
	model->LoadModel(j["model"]["filePath"]);
	return model;
}