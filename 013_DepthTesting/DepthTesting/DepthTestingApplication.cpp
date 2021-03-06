#include <DepthTestingApplication.h>

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

DepthTestingApplication::DepthTestingApplication() : OpenGLApplication(1500, 720, "DEPTH TESTING"), m_seeDepthBuffer(false), m_seeDepthBufferPrevValue(false)
{

}

void DepthTestingApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadShaders();
	LoadLights();
	LoadModels();
}

void DepthTestingApplication::OnDraw()
{
	if (m_seeDepthBuffer != m_seeDepthBufferPrevValue)
	{
		delete m_shader;
		m_seeDepthBufferPrevValue = m_seeDepthBuffer;
		if (m_seeDepthBuffer)
		{
			m_shader = new Shader("Data/Shaders/shader_depth_buffer.vert", "Data/Shaders/shader_depth_buffer.frag");
		}
		else
		{
			m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
		}
	}

	DrawModels();
	m_lightsSet.DebugDraw(m_camera);
}

void DepthTestingApplication::ProcessInput()
{
	OpenGLApplication::ProcessInput();
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void DepthTestingApplication::LoadShaders()
{
	m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
}

void DepthTestingApplication::LoadLights()
{
	DirectionalLight* directionalLight1 = new DirectionalLight();
	directionalLight1->SetPosition({ -1.f, -1.f, -1.f});
	directionalLight1->SetAmbient({ 0.2f, 0.2f, 0.2f });
	directionalLight1->SetDiffuse({ 0.5f, 0.5f, 0.5f });
	directionalLight1->SetSpecular({ 1.0f, 1.0f, 1.0f });

	m_lightsSet.AddDirectionalLight(directionalLight1);
}

void DepthTestingApplication::LoadMaterials()
{
	m_materials = {
		Material({ 0.1f, 0.1f, 0.1f}, { 0.6f, 0.6f, 0.6f}, { 1.0f, 1.0f, 1.0f}, 0.3f*128.f)
	};
}

void DepthTestingApplication::LoadModels()
{
	LoadModel({ 0.f, 0.f, 0.f }, "Data/models/sponza/sponza.obj");
}

void DepthTestingApplication::LoadModel(glm::vec3 position, std::string modelPath)
{
	AssimpModel* model = new AssimpModel(modelPath);

	glm::mat4 trans = model->GetTransform();
	trans = glm::translate(model->GetTransform(), position);
	float scale = 0.03f;
	trans = glm::scale(trans, { scale, scale, scale });
	model->SetTransform(trans);

	m_models.push_back(model);
}

void DepthTestingApplication::DrawModels()
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
		ImGui::Text("DEPTH TESTING");
		ImGui::End();
	}

	{
		ImGui::Begin("Options", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos({ 5,50 });
		ImGui::SetWindowSize({ 200, 60 });
		ImGui::PushItemWidth(100);
		ImGui::BeginChild("Child1");
		ImGui::Checkbox("See Depth Buffer", &m_seeDepthBuffer);
		ImGui::EndChild();
		ImGui::End();
	}
}