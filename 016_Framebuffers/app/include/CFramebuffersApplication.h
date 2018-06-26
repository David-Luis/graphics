#pragma once

#include <CCameraController.h>

#include <Engine/COpenGLApplication.h>
#include <Engine/Model/CMaterial.h>
#include <Engine/Scene/CBlendingScene.h>
#include <Engine/Light/CLightsSet.h>
#include <Engine/Render/CFramebuffer.h>

#include <vector>

class CModel;
class CShader;
class CTexture;

class CFramebuffersApplication : public COpenGLApplication
{
public:
	CFramebuffersApplication();
	~CFramebuffersApplication() override {}
	CFramebuffersApplication(const CFramebuffersApplication&) = delete;
	CFramebuffersApplication& operator=(CFramebuffersApplication const&) = delete;

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

	void LoadDefaultModel(CModel* model);
	void ConfigureModel(CModel* model);

	void SaveScene();
	void LoadScene();
	void SelectNextModel();

	void CreateShaders();
	void CreateLights();
	void CreateScene();

	CFramebuffer m_framebuffer;
	CShader* m_shader;
	CShader* m_shaderTexture2D;
	CBlendingScene m_scene;
	CModel* m_selectedModel;
	CTexture* m_texture2D;

	bool m_spacePressed;
	bool m_controlPressed;
	bool m_altPressed;
	bool m_enterPressed;
	bool m_savePressed;
	bool m_loadPressed;

	CCameraController m_cameraController;
};
