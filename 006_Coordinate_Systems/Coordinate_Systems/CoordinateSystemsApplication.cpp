#include <CoordinateSystemsApplication.h>

#include <Engine/Mesh.h>
#include <Engine/Texture.h>
#include <Engine/Shader.h>
#include <Engine/Model.h>

#include <GLFW/glfw3.h>
#include <Lib/imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>

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

CoordinateSystemsApplication::CoordinateSystemsApplication() : OpenGLApplication(800, 600, "Coordinate Systems")
{

}

void CoordinateSystemsApplication::OnInit()
{
	m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -3.0f));
	m_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_windowsWidth) / static_cast<float>(m_windowsHeight), 0.1f, 100.0f);

	LoadModels();
}

void CoordinateSystemsApplication::OnDraw()
{
	DrawModels();
}

void CoordinateSystemsApplication::LoadModels()
{
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (auto& position : cubePositions)
	{
		Model* model = LoadModel1();
		model->m_trans = glm::translate(model->m_trans, position);
		model->m_trans = glm::rotate(model->m_trans, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		m_models.push_back(model);
	}
}

Model* CoordinateSystemsApplication::LoadModel1()
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

	return new Model(shader, texture, mesh, &m_view, &m_projection);
}

void CoordinateSystemsApplication::DrawModels()
{
	int i = 0;
	for (const auto& model : m_models)
	{
		glm::vec3 pos = GetTranslationFromMat4(model->m_trans);
		model->m_trans = glm::mat4();
		model->m_trans = glm::translate(model->m_trans, pos);
		model->m_trans = glm::rotate(model->m_trans, (float)glfwGetTime() * glm::radians(50.0f) + i, glm::vec3(0.5f, 1.0f, 0.0f));
		model->Update();
		model->Draw();

		i++;
	}

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowPos({5,5});
	ImGui::Text("COORDINATE SYSTEMS");
	ImGui::End();
}