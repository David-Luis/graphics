#include <CameraApplication.h>

#include <Engine/Mesh.h>
#include <Engine/Texture.h>
#include <Engine/Shader.h>
#include <Engine/Model.h>

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

CameraApplication::CameraApplication() : OpenGLApplication(1500, 720, "Camera")
{

}

void CameraApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 0.0f, 1.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadModels();
}

void CameraApplication::OnDraw()
{
	DrawModels();
}

void CameraApplication::ProcessInput()
{
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void CameraApplication::LoadModels()
{
	Model* model = LoadModel1();
	model->m_trans = glm::translate(model->m_trans, {0.0f, 0.0f, -5.0f});
	m_models.push_back(model);
}

Model* CameraApplication::LoadModel1()
{
	std::vector<float> vertices = {
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// back
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	};

	std::vector<unsigned int> indices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3,
	};


	Shader* shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
	Mesh* mesh = new Mesh(vertices, indices);
	Texture* texture = new Texture("Data/Textures/wall.jpg");

	return new Model(shader, texture, mesh);
}

void CameraApplication::DrawModels()
{
	int i = 0;
	for (const auto& model : m_models)
	{
		glm::vec3 pos = GetTranslationFromMat4(model->m_trans);
		model->m_trans = glm::mat4();
		model->m_trans = glm::translate(model->m_trans, pos);
		model->m_trans = glm::rotate(model->m_trans, (float)glfwGetTime() * glm::radians(50.0f) + i, glm::vec3(0.5f, 1.0f, 0.0f));
		model->Update();
		model->Draw(&m_camera);

		i++;
	}

	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::SetNextWindowPos({ 5,5 });
		ImGui::Begin("Example Title", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize);
		ImGui::Text("CAMERA");
		ImGui::End();
	}

	
	{
		ImGui::Begin("Options", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos({ 5,50 });
		ImGui::PushItemWidth(100);
		ImGui::BeginChild("Child1");
			ImGui::SliderFloat("Camera Speed", &m_camera.MovementSpeed, 0.1f, 50.f);
			ImGui::SliderFloat("Camera Fov", &m_camera.Fov, 1.f, 45.f);
			ImGui::SliderFloat("Mouse Sens", &m_camera.MouseSensitivity, 0.1f, 0.9f);
		ImGui::EndChild();
		ImGui::End();
	}

	{
		//ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); 
		//ImGui::ShowDemoWindow();
	}
	
}