#include <CBlendingApplication.h>

#include <Engine/Model/Mesh.h>
#include <Engine/Texture/Texture.h>
#include <Engine/Shader/Shader.h>
#include <Engine/Model/CAssimpModel.h>
#include <Engine/Engine.h>
#include <Engine/Light/DirectionalLight.h>
#include <Engine/Light/PointLight.h>
#include <Engine/Light/SpotLight.h>

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

CBlendingApplication::CBlendingApplication() : OpenGLApplication(1500, 720, "STENCIL TESTING")
{

}

void CBlendingApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 1.0f, 8.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadShaders();
	LoadLights();
	LoadModels();
}

void CBlendingApplication::OnDraw()
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	m_models[0]->SetTransformComponents({ 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, {1, 1, 1}, 10);
	m_models[1]->SetTransformComponents({ -2.f, 0.f, -2.f }, { 1.f, 1.f, 1.f }, {1, 1, 1}, -10);
	DrawModels(m_shader);

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
	m_models[0]->SetTransformComponents({ 0.f, 0.f, 0.f }, { 1.1f, 1.1f, 1.1f }, {1, 1, 1}, 10);
	m_models[1]->SetTransformComponents({ -2.f, 0.f, -2.f }, { 1.1f, 1.1f, 1.1f }, {1, 1, 1}, -10);
	DrawModels(m_silueteShader);

	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);

	m_lightsSet.DebugDraw(m_camera);

	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::SetNextWindowPos({ 5,5 });
		ImGui::SetNextWindowSize({ 300, 100 });
		ImGui::Begin("Example Title", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize);
		ImGui::Text("STENCIL TESTING");
		ImGui::End();
	}
}

void CBlendingApplication::ProcessInput()
{
	OpenGLApplication::ProcessInput();
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void CBlendingApplication::LoadShaders()
{
	m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
	m_silueteShader = new Shader("Data/Shaders/siluete.vert", "Data/Shaders/siluete.frag");
}

void CBlendingApplication::LoadLights()
{
	PointLight* light1 = new PointLight();
	light1->SetPosition({ 1.f, 0.f, 10.f});
	light1->SetAmbient({ 0.2f, 0.2f, 0.2f });
	light1->SetDiffuse({ 0.5f, 0.5f, 0.5f });
	light1->SetSpecular({ 1.0f, 1.0f, 1.0f });

	m_lightsSet.AddPointLight(light1);

	DirectionalLight* light2 = new DirectionalLight();
	light2->SetPosition({ 1.f, 1.f, 10.f });
	light2->SetAmbient({ 0.2f, 0.2f, 0.2f });
	light2->SetDiffuse({ 0.0f, 0.0f, 0.0f });
	light2->SetSpecular({ 0.0f, 0.0f, 0.0f });

	m_lightsSet.AddDirectionalLight(light2);
}

void CBlendingApplication::LoadMaterials()
{
	m_materials = {
		Material({ 0.1f, 0.1f, 0.1f}, { 0.6f, 0.6f, 0.6f}, { 1.0f, 1.0f, 1.0f}, 0.3f*128.f)
	};
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
	Texture* textureDiffuse = Engine::assetsManager->GetTexture("Data/Textures/container.png");
	textureDiffuse->SetType("texture_diffuse");

	Engine::assetsManager->LoadTexture("Data/Textures/container_specular.png");
	Texture* textureSpecular = Engine::assetsManager->GetTexture("Data/Textures/container_specular.png");
	textureSpecular->SetType("texture_specular");

	std::vector<Texture*> textures = { textureDiffuse, textureSpecular };
	model->GetMeshes()[0]->SetTextures(textures);

	m_models.push_back(model);
}

void CBlendingApplication::DrawModels(Shader* shader)
{
	for (const auto& model : m_models)
	{
		model->Update();
		model->Draw(*shader, m_camera, m_lightsSet);
	}	
}