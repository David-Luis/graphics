#include <ModeLoadingApplication.h>

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

ModeLoadingApplication::ModeLoadingApplication() : OpenGLApplication(1500, 720, "Camera")
{

}

void ModeLoadingApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 8.0f, 12.0f);
	m_cameraController.SetCamera(&m_camera);

	LoadModels();
}

void ModeLoadingApplication::OnDraw()
{
	DrawModels();
}

void ModeLoadingApplication::ProcessInput()
{
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);
}

void ModeLoadingApplication::LoadModels()
{
	
	Model* model = new Model("Data/Models/nanosuit/nanosuit.obj");
	model->m_trans = glm::translate(model->m_trans, {0.0f, 0.0f, -10.0f});
	m_models.push_back(model);
	

	/*
	std::vector<Vertex> vertices = {
		{-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
		{0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f },
		{-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f },
		// back
		{-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
		{0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
		{0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f },
		{-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f },
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

	std::vector<Texture*> textures;

	std::vector<Mesh*> meshes = { new Mesh(vertices, indices, textures) };

	Model* model = new Model(meshes);
	model->m_trans = glm::translate(model->m_trans, { 0.0f, 0.0f, -10.0f });
	m_models.push_back(model);
	*/

	m_shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
}

void ModeLoadingApplication::DrawModels()
{
	for (const auto& model : m_models)
	{
		model->Update();
		model->Draw(*m_shader, m_camera);
	}	
}