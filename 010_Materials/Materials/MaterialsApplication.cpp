#include <MaterialsApplication.h>

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

MaterialsApplication::MaterialsApplication() : OpenGLApplication(1500, 720, "Model Loading")
{

}

void MaterialsApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadModels();
}

void MaterialsApplication::OnDraw()
{
	DrawModels();
	for (const auto& light : m_lights)
	{
		light->DebugDraw(m_camera);
	}
}

void MaterialsApplication::ProcessInput()
{
	OpenGLApplication::ProcessInput();
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void MaterialsApplication::LoadModels()
{
	LoadModel({ -2.0f, -2.0f, -3.0f }, "Data/models/sphere.obj");
	LoadModel({ 2.0f, -2.0f, -3.0f }, "Data/models/cube.obj");
	LoadModel({ -2.0f, 2.0f, -3.0f }, "Data/models/sphere.obj");
	LoadModel({ 0,0,-2 }, "Data/models/cube.obj");

	m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");

	PointLight* light = new PointLight();
	light->SetColor({ 0.6f, 0.1f, 0.1f });
	m_lights.push_back(light);
}

void MaterialsApplication::LoadModel(glm::vec3 position, std::string modelPath)
{
	AssimpModel* model = new AssimpModel(modelPath);
	model->SetTransform(glm::translate(model->GetTransform(), position));
	glm::mat4 trans = model->GetTransform();
	trans = glm::rotate(trans, 0.f, glm::vec3(1, 1, 0));
	model->SetTransform(trans);
	m_models.push_back(model);
}

void MaterialsApplication::DrawModels()
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
		ImGui::Text("BASIC LIGHTING");
		ImGui::End();
	}
}