#pragma once

#include <CameraController.h>

#include <Engine/OpenGLApplication.h>
#include <Engine/Model/Material.h>
#include <Engine/Light/LightsSet.h>

#include <vector>

class Model;
class Shader;

class BlendingApplication : public OpenGLApplication
{
public:
	BlendingApplication();
	~BlendingApplication() override {}
	BlendingApplication(const BlendingApplication&) = delete;
	BlendingApplication& operator=(BlendingApplication const&) = delete;

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

	Shader* m_shader;
	Shader* m_silueteShader;
	std::vector<Model*> m_models;
	std::vector<Material> m_materials;
	LightsSet m_lightsSet;

	CameraController m_cameraController;
};
