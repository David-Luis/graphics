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

MaterialsApplication::MaterialsApplication() : OpenGLApplication(1500, 720, "Materials")
{

}

void MaterialsApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 0.0f, 20.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadMaterials();
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

void MaterialsApplication::LoadMaterials()
{
	m_materials = {
		Material({ 0.0215f, 0.1745f, 0.0215f}, { 0.07568f, 0.61424f, 0.07568f}, { 0.633f, 0.727811f, 0.633f}, 0.6f*128.f),			//esmerald
		Material({ 0.25f, 0.20725f, 0.20725f },{ 1.f, 0.829f, 0.829f },{ 0.296648f, 0.296648f, 0.296648f }, 0.088f*128.f),			//pearl
		Material({ 0.2125f, 0.1275f, 0.054f },{ 0.714f, 0.4284f, 0.18144f },{ 0.393548f, 0.271906f, 0.166721f }, 0.2f*128.f),		//bronze
		Material({ 0.24725f, 0.1995f, 0.0745f },{ 0.75164f, 0.60648f, 0.22648f },{ 0.628281f, 0.555802f, 0.366065f }, 0.4*128.f),	//gold
		Material({ 0.0f, 0.1f, 0.06f },{ 0.0f, 0.50980392f, 0.50980392f },{ 0.50196078f, 0.50196078f, 0.50196078f }, 0.25f*128.f),	//cyan plastic
		Material({ 0.0f, 0.0f, 0.0f },{ 0.5f, 0.0f, 0.0f },{ 0.7f, 0.6f, 0.6f }, 0.25f*128.f),										//red plastic
		Material({ 0.0f, 0.05f, 0.0f },{ 0.4f, 0.5f, 0.4f },{ 0.04f, 0.7f, 0.04f }, 0.078125f*128.f),								//green rubber
		Material({ 0.05f, 0.05f, 0.0f },{ 0.5f, 0.5f, 0.4f },{ 0.7f, 0.7f, 0.04f }, 0.078125f*128.f)								//yellow rubber
	};
}

void MaterialsApplication::LoadModels()
{
	LoadModel({ -15, 5.0f, -5.0f }, "Data/models/cube.obj", m_materials[0]);
	LoadModel({ -5.f, 5.0f, -5.0f }, "Data/models/cube.obj", m_materials[1]);
	LoadModel({ 5.0f, 5.0f, -5.0f }, "Data/models/cube.obj", m_materials[2]);
	LoadModel({ 15.0f, 5.0f, -5.0f }, "Data/models/cube.obj", m_materials[3]);

	LoadModel({ -15, -5.0f, -5.0f }, "Data/models/cube.obj", m_materials[4]);
	LoadModel({ -5.f, -5.0f, -5.0f }, "Data/models/cube.obj", m_materials[5]);
	LoadModel({ 5.0f, -5.0f, -5.0f }, "Data/models/cube.obj", m_materials[6]);
	LoadModel({ 15.0f, -5.0f, -5.0f }, "Data/models/cube.obj", m_materials[7]);
	
	m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");

	PointLight* light = new PointLight();

	light->SetPosition({ 0.0f, 0.0f, 10.f });
	light->SetAmbient({ 1.0f, 1.0f, 1.0f });
	light->SetDiffuse({ 1.0f, 1.0f, 1.0f });
	light->SetSpecular({ 1.0f, 1.0f, 1.0f });

	m_lights.push_back(light);
}

void MaterialsApplication::LoadModel(glm::vec3 position, std::string modelPath, Material& material)
{
	AssimpModel* model = new AssimpModel(modelPath);
	model->GetMeshes()[0]->SetMaterial(material);

	model->SetTransform(glm::translate(model->GetTransform(), position));
	glm::mat4 trans = model->GetTransform();
	trans = glm::scale(trans, glm::vec3(5.f, 5.f, 5.f));
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
		ImGui::Text("MATERIALS");
		ImGui::End();
	}
}