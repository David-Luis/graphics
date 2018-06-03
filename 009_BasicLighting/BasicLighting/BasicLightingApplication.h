#pragma once

#include <CameraController.h>

#include <Engine/OpenGLApplication.h>

#include <vector>

class Model;
class Shader;
class PointLight;

class BasicLightingApplication : public OpenGLApplication
{
public:
	BasicLightingApplication();
	~BasicLightingApplication() override {}
	BasicLightingApplication(const BasicLightingApplication&) = delete;
	BasicLightingApplication& operator=(BasicLightingApplication const&) = delete;

private:
	void OnInit() override;
	void OnDraw() override;
	void ProcessInput() override;

	void LoadModels();
	void LoadModel(glm::vec3 position, std::string modelPath);

	void DrawModels();

	Shader* m_shader;
	std::vector<Model*> m_models;
	PointLight* m_pointLight;

	CameraController m_cameraController;
};
