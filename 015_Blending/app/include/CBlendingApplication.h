#pragma once

#include <CCameraController.h>

#include <Engine/COpenGLApplication.h>
#include <Engine/Model/CMaterial.h>
#include <Engine/Light/CLightsSet.h>

#include <vector>

class Model;
class Shader;

class CBlendingApplication : public COpenGLApplication
{
public:
	CBlendingApplication();
	~CBlendingApplication() override {}
	CBlendingApplication(const CBlendingApplication&) = delete;
	CBlendingApplication& operator=(CBlendingApplication const&) = delete;

private:
	void OnInit() override;
	void OnDraw() override;
	void ProcessInput() override;

	void LoadShaders();
	void LoadLights();
	void LoadMaterials();
	void LoadModels();
	void LoadModel(glm::vec3 position, glm::vec3 scale, std::string modelPath);

	void DrawModels(Shader* shader);

	CShader* m_shader;
	CShader* m_silueteShader;
	std::vector<CModel*> m_models;
	std::vector<CMaterial> m_materials;
	CLightsSet m_lightsSet;

	CCameraController m_cameraController;
};
