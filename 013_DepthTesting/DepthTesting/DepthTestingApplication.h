#pragma once

#include <CameraController.h>

#include <Engine/OpenGLApplication.h>
#include <Engine/Model/Material.h>
#include <Engine/Light/LightsSet.h>

#include <vector>

class Model;
class Shader;

class DepthTestingApplication : public OpenGLApplication
{
public:
	DepthTestingApplication();
	~DepthTestingApplication() override {}
	DepthTestingApplication(const DepthTestingApplication&) = delete;
	DepthTestingApplication& operator=(DepthTestingApplication const&) = delete;

private:
	void OnInit() override;
	void OnDraw() override;
	void ProcessInput() override;

	void LoadShaders();
	void LoadLights();
	void LoadMaterials();
	void LoadModels();
	void LoadModel(glm::vec3 position, std::string modelPath);

	void DrawModels();

	Shader* m_shader;
	std::vector<Model*> m_models;
	std::vector<Material> m_materials;
	LightsSet m_lightsSet;

	CameraController m_cameraController;

	bool m_seeDepthBuffer;
	bool m_seeDepthBufferPrevValue;
};
