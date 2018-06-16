#pragma once

#include <CCameraController.h>

#include <Engine/COpenGLApplication.h>
#include <Engine/Model/CMaterial.h>
#include <Engine/Scene/CScene.h>
#include <Engine/Light/CLightsSet.h>

#include <vector>

class CModel;
class CShader;

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

	void ProcessInputEditorCreateModel();
	void ProcessInputIterateModel();
	void ProcessInputEditorMoveModel();
	void ProcessInputEditorRotateModel();
	void ProcessInputEditorScaleModel();

	void LoadShaders();
	void LoadLights();
	void LoadModels();
	CModel* LoadModel(glm::vec3 position, glm::vec3 scale, std::string modelPath);

	CShader* m_shader;
	CScene m_scene;
	CModel* m_selectedModel;

	bool m_spacePressed;
	bool m_controlPressed;
	bool m_altPressed;
	bool m_enterPressed;

	CCameraController m_cameraController;
};
