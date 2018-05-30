#pragma once

#include <CameraController.h>

#include <Engine/OpenGLApplication.h>

#include <vector>

class Model;
class Shader;

class ModeLoadingApplication : public OpenGLApplication
{
public:
	ModeLoadingApplication();
	~ModeLoadingApplication() override {}
	ModeLoadingApplication(const ModeLoadingApplication&) = delete;
	ModeLoadingApplication& operator=(ModeLoadingApplication const&) = delete;

private:
	void OnInit() override;
	void OnDraw() override;
	void ProcessInput() override;

	void LoadModels();
	void DrawModels();

	Shader* m_shader;
	std::vector<Model*> m_models;

	CameraController m_cameraController;
};
