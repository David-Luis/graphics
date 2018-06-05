#include <LightingMapsApplication.h>

#include <Engine/Model/Mesh.h>
#include <Engine/Texture/Texture.h>
#include <Engine/Shader/Shader.h>
#include <Engine/Model/AssimpModel.h>
#include <Engine/Engine.h>
#include <Engine/Light/PointLight.h>

#include <GLFW/glfw3.h>
#include <Lib/imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

static glm::vec3 GetTranslationFromMat4(glm::mat4& mat)
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(mat, scale, rotation, translation, skew, perspective);

	return translation;
}

LightingMapsApplication::LightingMapsApplication() : OpenGLApplication(1500, 720, "Materials")
{

}

void LightingMapsApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadMaterials();
	LoadModels();
}

void LightingMapsApplication::OnDraw()
{
	DrawModels();
	for (const auto& light : m_lights)
	{
		light->DebugDraw(m_camera);
	}
}

void LightingMapsApplication::ProcessInput()
{
	OpenGLApplication::ProcessInput();
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void LightingMapsApplication::LoadMaterials()
{
	m_materials = {
		Material({ 0.1f, 0.1f, 0.1f}, { 0.6f, 0.6f, 0.6f}, { 1.0f, 1.0f, 1.0f}, 0.3f*128.f)
	};
}

void LightingMapsApplication::LoadModels()
{
	LoadModel({ 0, 0.0f, -1.0f }, "Data/models/cube.obj", m_materials[0]);
	
	m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");

	PointLight* light = new PointLight();

	light->SetPosition({ 1.0f, 0.0f, 10.f });
	light->SetAmbient({ 1.0f, 1.0f, 1.0f });
	light->SetDiffuse({ 1.0f, 1.0f, 1.0f });
	light->SetSpecular({ 1.0f, 1.0f, 1.0f });

	m_lights.push_back(light);
}

void LightingMapsApplication::LoadModel(glm::vec3 position, std::string modelPath, Material& material)
{
	AssimpModel* model = new AssimpModel(modelPath);

	model->SetTransform(glm::translate(model->GetTransform(), position));
	glm::mat4 trans = model->GetTransform();
	model->SetTransform(trans);

	model->GetMeshes()[0]->SetMaterial(material);

	Engine::assetsManager->LoadTexture("Data/Textures/container.png");
	Texture* textureDiffuse = Engine::assetsManager->GetTexture("Data/Textures/container.png");
	textureDiffuse->SetType("texture_diffuse");

	Engine::assetsManager->LoadTexture("Data/Textures/container_specular.png");
	Texture* textureSpecular = Engine::assetsManager->GetTexture("Data/Textures/container_specular.png");
	textureSpecular->SetType("texture_specular");

	std::vector<Texture*> textures = { textureDiffuse, textureSpecular };
	model->GetMeshes()[0]->SetTextures(textures);

	m_models.push_back(model);
}

void LightingMapsApplication::DrawModels()
{
	for (const auto& model : m_models)
	{
		model->Update();
		model->Draw(*m_shader, m_camera, m_lights);
	}	

	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::SetNextWindowPos({ 5,5 });
		ImGui::Begin("Example Title", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize);
		ImGui::Text("MATERIALS");
		ImGui::End();
	}
}