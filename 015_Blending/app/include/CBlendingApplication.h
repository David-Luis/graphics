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

	static CModel* CreateAndAddModel();
	static void LoadDefaultModel(CModel* model);
	static void ConfigureModel(CModel* model);

private:
	void OnInit() override;
	void OnDraw() override;
	void ProcessInput() override;

	void ProcessInputEditorCreateModel();
	void ProcessInputIterateModel();
	void ProcessInputEditorMoveModel();
	void ProcessInputEditorRotateModel();
	void ProcessInputEditorScaleModel();
	void ProcessInputSaveLoadScene();

	void SaveScene();
	void LoadScene();
	void SelectNextModel();

	void CreateShaders();
	void CreateLights();
	void CreateScene();

	static CShader* m_shader;
	static CScene m_scene;
	CModel* m_selectedModel;

	bool m_spacePressed;
	bool m_controlPressed;
	bool m_altPressed;
	bool m_enterPressed;
	bool m_savePressed;
	bool m_loadPressed;

	CCameraController m_cameraController;
};
