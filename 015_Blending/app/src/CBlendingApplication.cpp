#include <CBlendingApplication.h>

#include <Engine/Model/CMesh.h>
#include <Engine/Texture/CTexture.h>
#include <Engine/Shader/CShader.h>
#include <Engine/Model/CAssimpModel.h>
#include <Engine/Engine.h>
#include <Engine/Light/CDirectionalLight.h>
#include <Engine/Light/CPointLight.h>
#include <Engine/Light/CSpotLight.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
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

CBlendingApplication::CBlendingApplication() : COpenGLApplication(1500, 720, "BLENDING")
{

}

void CBlendingApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 1.0f, 8.0f);
	m_cameraController.SetCamera(&m_camera);
	m_scene.SetCamera(&m_camera);

	LoadShaders();
	LoadLights();
	LoadModels();
}

void CBlendingApplication::OnDraw()
{
	m_scene.Draw();

	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::SetNextWindowPos({ 5,5 });
		ImGui::SetNextWindowSize({ 300, 100 });
		ImGui::Begin("Example Title", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize);
		ImGui::Text("BLENDING");
		ImGui::End();
	}
}

void CBlendingApplication::ProcessInput()
{
	COpenGLApplication::ProcessInput();
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void CBlendingApplication::LoadShaders()
{
	m_shader = new CShader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
}

void CBlendingApplication::LoadLights()
{
	CLightsSet* lightsSet = new CLightsSet();

	CPointLight* light1 = new CPointLight();
	light1->SetPosition({ 1.f, 0.f, 10.f});
	light1->SetAmbient({ 0.2f, 0.2f, 0.2f });
	light1->SetDiffuse({ 0.5f, 0.5f, 0.5f });
	light1->SetSpecular({ 1.0f, 1.0f, 1.0f });

	lightsSet->AddPointLight(light1);

	CDirectionalLight* light2 = new CDirectionalLight();
	light2->SetPosition({ 1.f, 1.f, 10.f });
	light2->SetAmbient({ 0.2f, 0.2f, 0.2f });
	light2->SetDiffuse({ 0.0f, 0.0f, 0.0f });
	light2->SetSpecular({ 0.0f, 0.0f, 0.0f });

	lightsSet->AddDirectionalLight(light2);

	m_scene.SetLightsSet(lightsSet);
}

void CBlendingApplication::LoadModels()
{
	LoadModel({ 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, "Data/models/cube.obj");
	LoadModel({ -2.f, 0.f, -2.f }, { 1.f, 1.f, 1.f }, "Data/models/cube.obj");
	//LoadModel({ 0.f, -0.5f, 0.f }, { 50.f, 0.01f, 50.f }, "Data/models/cube.obj");
}

void CBlendingApplication::LoadModel(glm::vec3 position, glm::vec3 scale, std::string modelPath)
{
	CAssimpModel* model = new CAssimpModel(modelPath);

	glm::mat4 trans;
	trans = glm::translate(model->GetTransform(), position);
	trans = glm::scale(trans, scale);
	model->SetTransform(trans);

	Engine::assetsManager->LoadTexture("Data/Textures/container.png");
	CTexture* textureDiffuse = Engine::assetsManager->GetTexture("Data/Textures/container.png");
	textureDiffuse->SetType("texture_diffuse");

	Engine::assetsManager->LoadTexture("Data/Textures/container_specular.png");
	CTexture* textureSpecular = Engine::assetsManager->GetTexture("Data/Textures/container_specular.png");
	textureSpecular->SetType("texture_specular");

	std::vector<CTexture*> textures = { textureDiffuse, textureSpecular };
	model->GetMeshes()[0]->SetTextures(textures);

	model->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.1f, 0.1f }, { 0.6f, 0.6f, 0.6f }, { 1.0f, 1.0f, 1.0f }, 0.3f*128.f));

	model->SetShader(m_shader);

	m_scene.AddModel(model);
}