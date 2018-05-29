#pragma once

#include <CameraController.h>

#include <Engine/OpenGLApplication.h>

#include <vector>

class Model;

class CameraApplication : public OpenGLApplication
{
public:
	CameraApplication();
	~CameraApplication() override {}
	CameraApplication(const CameraApplication&) = delete;
	CameraApplication& operator=(CameraApplication const&) = delete;

private:
	void OnInit() override;
	void OnDraw() override;
	void ProcessInput() override;

	void LoadModels();
	Model* LoadModel1();
	Model* LoadModel2();
	void DrawModels();

	std::vector<Model*> m_models;

	CameraController m_cameraController;
};
