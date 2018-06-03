#include <BasicLightingApplication.h>

#include <Engine/Mesh.h>
#include <Engine/Texture.h>
#include <Engine/Shader.h>
#include <Engine/AssimpModel.h>
#include <Engine/Engine.h>
#include <Engine/AssetsManager.h>
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

BasicLightingApplication::BasicLightingApplication() : OpenGLApplication(1500, 720, "Model Loading")
{

}

void BasicLightingApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadModels();
}

void BasicLightingApplication::OnDraw()
{
	DrawModels();
	m_pointLight->DebugDraw(m_camera);
}

void BasicLightingApplication::ProcessInput()
{
	OpenGLApplication::ProcessInput();
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void BasicLightingApplication::LoadModels()
{
	LoadModel({ -2.0f, -2.0f, -3.0f }, "Data/models/sphere.obj");
	LoadModel({ 2.0f, -2.0f, -3.0f }, "Data/models/cube.obj");
	LoadModel({ -2.0f, 2.0f, -3.0f }, "Data/models/sphere.obj");
	LoadModel({ 0,0,-2 }, "Data/models/cube.obj");

	m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");

	m_pointLight = new PointLight();
	m_pointLight->SetColor({ 0.6f, 0.1f, 0.1f });
}

void BasicLightingApplication::LoadModel(glm::vec3 position, std::string modelPath)
{
	AssimpModel* model = new AssimpModel(modelPath);
	model->SetTransform(glm::translate(model->GetTransform(), position));
	glm::mat4 trans = model->GetTransform();
	trans = glm::rotate(trans, 0.f, glm::vec3(1, 1, 0));
	model->SetTransform(trans);
	m_models.push_back(model);
}

void BasicLightingApplication::DrawModels()
{
	m_shader->Use();
	m_pointLight->Use(*m_shader);

	for (const auto& model : m_models)
	{
		model->Update();
		model->Draw(*m_shader, m_camera);
	}	

	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::SetNextWindowPos({ 5,5 });
		ImGui::Begin("Example Title", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize);
		ImGui::Text("BASIC LIGHTING");
		ImGui::End();
	}
}