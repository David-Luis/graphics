#include <LightCastersApplication.h>

#include <Engine/Model/Mesh.h>
#include <Engine/Texture/Texture.h>
#include <Engine/Shader/Shader.h>
#include <Engine/Model/AssimpModel.h>
#include <Engine/Engine.h>
#include <Engine/Light/DirectionalLight.h>
#include <Engine/Light/PointLight.h>
#include <Engine/Light/SpotLight.h>

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

LightCastersApplication::LightCastersApplication() : OpenGLApplication(1500, 720, "Materials")
{

}

void LightCastersApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadLights();
	LoadMaterials();
	LoadModels();
}

void LightCastersApplication::OnDraw()
{
	DrawModels();
	m_lightsSet.DebugDraw(m_camera);
}

void LightCastersApplication::ProcessInput()
{
	OpenGLApplication::ProcessInput();
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void LightCastersApplication::LoadLights()
{
	/*
	PointLight* light1 = new PointLight();

	light1->SetPosition({ 1.0f, 0.0f, 10.f });
	light1->SetAmbient({ 1.0f, 1.0f, 1.0f });
	light1->SetDiffuse({ 1.0f, 1.0f, 1.0f });
	light1->SetSpecular({ 1.0f, 1.0f, 1.0f });
	//light1->SetAttenuation(0.01f, 0.01f, 0.01f);
	//m_lightsSet.AddPointLight(light1);
	
	PointLight* light2 = new PointLight();

	light2->SetPosition({ 6.0f, 2.0f, -10.f });
	light2->SetAmbient({ 1.0f, 1.0f, 1.0f });
	light2->SetDiffuse({ 1.0f, 1.0f, 1.0f });
	light2->SetSpecular({ 1.0f, 1.0f, 1.0f });
	light2->SetAttenuation(0.01f, 0.01f, 0.01f);

	m_lightsSet.AddPointLight(light1);
	m_lightsSet.AddPointLight(light2);

	
	DirectionalLight* dirLight1 = new DirectionalLight();
	dirLight1->SetDirection({ 1.0f, 0.0f, 0.f });
	dirLight1->SetAmbient({ 1.0f, 1.0f, 1.0f });
	dirLight1->SetDiffuse({ 1.0f, 1.0f, 1.0f });
	dirLight1->SetSpecular({ 1.0f, 1.0f, 1.0f });

	m_lightsSet.AddDirectionalLight(dirLight1);
	*/
	SpotLight* spotLight1 = new SpotLight();

	spotLight1->SetPosition({ 0.0f, 0.0f, 2.f });
	spotLight1->SetAmbient({ 0.0f, 0.0f, 0.0f });
	spotLight1->SetDiffuse({ 0.1f, 0.1f, 0.1f });
	spotLight1->SetSpecular({ 1.0f, 1.0f, 1.0f });
	spotLight1->SetAttenuation(0.01f, 0.01f, 0.01f);
	spotLight1->SetCutoff(4.f, 12.f);

	m_lightsSet.AddSpotLight(spotLight1);

	SpotLight* spotLight2 = new SpotLight();

	spotLight2->SetPosition({ 4.0f, 3.f, -6.f });
	spotLight2->SetDirection({ -1.0f, -1.f, 0.f });
	spotLight2->SetAmbient({ 0.0f, 0.0f, 0.0f });
	spotLight2->SetDiffuse({ 0.1f, 0.1f, 0.1f });
	spotLight2->SetSpecular({ 1.0f, 1.0f, 1.0f });
	spotLight2->SetAttenuation(0.01f, 0.01f, 0.01f);
	spotLight2->SetCutoff(3.f, 5.f);

	m_lightsSet.AddSpotLight(spotLight2);

	DirectionalLight* dirLight1 = new DirectionalLight();
	dirLight1->SetDirection({ 1.0f, -1.0f, -1.f });
	dirLight1->SetAmbient({ 0.0f, 0.0f, 0.0f });
	dirLight1->SetDiffuse({ 0.5f, 0.5f, 0.5f });
	dirLight1->SetSpecular({ 1.0f, 1.0f, 1.0f });

	m_lightsSet.AddDirectionalLight(dirLight1);
}

void LightCastersApplication::LoadMaterials()
{
	m_materials = {
		Material({ 0.1f, 0.1f, 0.1f}, { 0.6f, 0.6f, 0.6f}, { 1.0f, 1.0f, 1.0f}, 0.3f*128.f)
	};
}

void LightCastersApplication::LoadModels()
{
	LoadModel({ 0, 0.0f, -1.0f }, "Data/models/cube.obj", m_materials[0]);
	LoadModel({ 1, 0.0f, -6.0f }, "Data/models/cube.obj", m_materials[0]);
	LoadModel({ 3, 0.0f, -11.0f }, "Data/models/cube.obj", m_materials[0]);
	LoadModel({ 5, 0.0f, -16.0f }, "Data/models/cube.obj", m_materials[0]);
	
	m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
}

void LightCastersApplication::LoadModel(glm::vec3 position, std::string modelPath, Material& material)
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

void LightCastersApplication::DrawModels()
{
	for (const auto& model : m_models)
	{
		model->Update();
		model->Draw(*m_shader, m_camera, m_lightsSet);
	}	

	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::SetNextWindowPos({ 5,5 });
		ImGui::Begin("Example Title", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize);
		ImGui::Text("LIGHT CASTERS");
		ImGui::End();
	}
}