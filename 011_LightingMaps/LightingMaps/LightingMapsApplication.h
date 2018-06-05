#pragma once

#include <CameraController.h>

#include <Engine/OpenGLApplication.h>
#include <Engine/Model/Material.h>

#include <vector>

class Model;
class Shader;
class Light;

class LightingMapsApplication : public OpenGLApplication
{
public:
	LightingMapsApplication();
	~LightingMapsApplication() override {}
	LightingMapsApplication(const LightingMapsApplication&) = delete;
	LightingMapsApplication& operator=(LightingMapsApplication const&) = delete;

private:
	void OnInit() override;
	void OnDraw() override;
	void ProcessInput() override;

	void LoadMaterials();
	void LoadModels();
	void LoadModel(glm::vec3 position, std::string modelPath, Material& material);

	void DrawModels();

	Shader* m_shader;
	std::vector<Model*> m_models;
	std::vector<Material> m_materials;
	std::vector<Light*> m_lights;

	CameraController m_cameraController;
};
