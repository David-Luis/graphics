#include <CFramebuffersApplication.h>

#include <Engine/Model/CMesh.h>
#include <Engine/Texture/CTexture.h>
#include <Engine/Shader/CShader.h>
#include <Engine/Model/CAssimpModel.h>
#include <Engine/Model/CModelFactory.h>
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
#include <fstream>

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

CFramebuffersApplication::CFramebuffersApplication() : COpenGLApplication(1500, 720, "FRAMEBUFFERS")
	, m_selectedModel(nullptr)
	, m_controlPressed(false)
	, m_altPressed(false)
	, m_enterPressed(false)
{

}

void CFramebuffersApplication::OnInit()
{
	m_camera.Position = glm::vec3(0.0f, 1.0f, 8.0f);
	m_cameraController.SetCamera(&m_camera);
	m_scene.SetCamera(&m_camera);

	CreateShaders();
	CreateLights();
	CreateScene();
}

void CFramebuffersApplication::OnDraw()
{
	m_scene.Draw();

	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::SetNextWindowPos({ 5,5 });
		ImGui::SetNextWindowSize({ 300, 100 });
		ImGui::Begin("Example Title", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoResize);
		ImGui::Text("FRAME BUFFERS");
		ImGui::End();
	}
}

void CFramebuffersApplication::ProcessInput()
{
	COpenGLApplication::ProcessInput();
	m_cameraController.ProcessInput(m_window, m_deltaMousePosition, m_deltaTime);

	ProcessInputEditorCreateModel();
	ProcessInputIterateModel();
	ProcessInputEditorMoveModel();
	ProcessInputEditorRotateModel();
	ProcessInputEditorScaleModel();
	ProcessInputSaveLoadScene();
}

void CFramebuffersApplication::ProcessInputEditorCreateModel()
{
	if ((glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) && !m_spacePressed)
	{
		m_spacePressed = true;
		if (m_selectedModel)
		{
			m_selectedModel->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.1f, 0.1f }, { 0.6f, 0.6f, 0.6f }, { 1.0f, 1.0f, 1.0f }, 0.3f*128.f));
		}

		m_selectedModel = CModelFactory::CreateModel();
		LoadDefaultModel(m_selectedModel);
		ConfigureModel(m_selectedModel);
		m_scene.AddModel(m_selectedModel);
		m_selectedModel->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.0f, 0.0f }, { 0.6f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 0.3f*128.f));
	}

	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		m_spacePressed = false;
	}
}

void CFramebuffersApplication::ProcessInputIterateModel()
{
	if ((glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS) && !m_enterPressed && m_selectedModel)
	{
		m_enterPressed = true;

		SelectNextModel();
	}

	if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_RELEASE)
	{
		m_enterPressed = false;
	}
}

void CFramebuffersApplication::ProcessInputEditorMoveModel()
{
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_controlPressed = true;
	}
	else if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		m_controlPressed = false;
	}

	if (m_controlPressed && !m_altPressed && m_selectedModel)
	{
		const float speed = 0.075f;
		if ((glfwGetKey(m_window, GLFW_KEY_KP_4) == GLFW_PRESS))
		{
			m_selectedModel->Translate({ -speed, 0.f, 0.f });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_6) == GLFW_PRESS))
		{
			m_selectedModel->Translate({ speed, 0.f, 0.f });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_8) == GLFW_PRESS))
		{
			m_selectedModel->Translate({ 0.f, 0.f, -speed });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_5) == GLFW_PRESS))
		{
			m_selectedModel->Translate({ 0.f, 0.f, speed });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_7) == GLFW_PRESS))
		{
			m_selectedModel->Translate({ 0.f, speed, 0.f });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_9) == GLFW_PRESS))
		{
			m_selectedModel->Translate({ 0.f, -speed, 0.f });
		}
	}
}

void CFramebuffersApplication::ProcessInputEditorRotateModel()
{
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		m_altPressed = true;
	}
	else if (glfwGetKey(m_window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
	{
		m_altPressed = false;
	}

	if (m_altPressed && !m_controlPressed && m_selectedModel)
	{
		const float speed = 0.02f;
		if ((glfwGetKey(m_window, GLFW_KEY_KP_4) == GLFW_PRESS))
		{
			m_selectedModel->Rotate(speed, { 0.f, 1.f, 0.f });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_6) == GLFW_PRESS))
		{
			m_selectedModel->Rotate(speed, { 0.f, -1.f, 0.f });
		}																						
		if ((glfwGetKey(m_window, GLFW_KEY_KP_8) == GLFW_PRESS))								
		{			
			m_selectedModel->Rotate(speed, { 1.f, 0.f, 0.f });
		}																						
		if ((glfwGetKey(m_window, GLFW_KEY_KP_5) == GLFW_PRESS))								
		{		
			m_selectedModel->Rotate(speed, { -1.f, 0.f, 0.f });
		}																						
		if ((glfwGetKey(m_window, GLFW_KEY_KP_7) == GLFW_PRESS))								
		{		
			m_selectedModel->Rotate(speed, { 0.f, 0.f, 1.f });
		}																						
		if ((glfwGetKey(m_window, GLFW_KEY_KP_9) == GLFW_PRESS))								
		{		
			m_selectedModel->Rotate(speed, { 0.f, 0.f, -1.f });
		}
	}
}

void CFramebuffersApplication::ProcessInputEditorScaleModel()
{
	if (m_altPressed && m_controlPressed && m_selectedModel)
	{
		const float speed = 1.01f;
		if ((glfwGetKey(m_window, GLFW_KEY_KP_4) == GLFW_PRESS))
		{
			m_selectedModel->Scale({ 1.f / speed, 1.f, 1.f });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_6) == GLFW_PRESS))
		{
			m_selectedModel->Scale({ speed, 1.f, 1.f });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_8) == GLFW_PRESS))
		{
			m_selectedModel->Scale({ 1.f, 1.f, speed });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_5) == GLFW_PRESS))
		{
			m_selectedModel->Scale({ 1., 1.f, 1.f / speed });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_7) == GLFW_PRESS))
		{
			m_selectedModel->Scale({ 1.f, speed, 1.f });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_9) == GLFW_PRESS))
		{
			m_selectedModel->Scale({ 1., 1.f / speed, 1.f });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_1) == GLFW_PRESS))
		{
			m_selectedModel->Scale({ 1.f / speed, 1.f / speed, 1.f / speed });
		}
		if ((glfwGetKey(m_window, GLFW_KEY_KP_3) == GLFW_PRESS))
		{
			m_selectedModel->Scale({ speed, speed, speed });
		}
	}
}

void CFramebuffersApplication::ProcessInputSaveLoadScene()
{
	if ((glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_PRESS) && !m_savePressed)
	{
		m_savePressed = true;

		SaveScene();
	}

	if ((glfwGetKey(m_window, GLFW_KEY_F5) == GLFW_PRESS) && !m_loadPressed)
	{
		m_loadPressed = true;

		LoadScene();
		SelectNextModel();
	}

	if (glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_RELEASE)
	{
		m_savePressed = false;
	}

	if (glfwGetKey(m_window, GLFW_KEY_F5) == GLFW_RELEASE)
	{
		m_loadPressed = false;
	}
}

void CFramebuffersApplication::SaveScene()
{
	std::ofstream sceneFile;
	sceneFile.open("Data/scene1");
	sceneFile << m_scene << std::endl;
	sceneFile.close();
}

void CFramebuffersApplication::LoadScene()
{
	m_scene.Clear();

	std::ifstream sceneFile;
	sceneFile.open("Data/scene1");
	if (sceneFile.is_open())
	{
		sceneFile >> m_scene;
		sceneFile.close();
	}

	for (auto& model : m_scene.GetModels())
	{
		ConfigureModel(model);
	}
}

void CFramebuffersApplication::SelectNextModel()
{
	if (m_selectedModel)
	{
		m_selectedModel->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.1f, 0.1f }, { 0.6f, 0.6f, 0.6f }, { 1.0f, 1.0f, 1.0f }, 0.3f*128.f));
	}

	auto models = m_scene.GetModels();
	int i;
	for (i = 0; i < static_cast<int>(models.size()); i++)
	{
		if (models[i] == m_selectedModel)
		{
			i++;
			break;
		}
	}

	if (models.size() > 0)
	{
		m_selectedModel = models[i%models.size()];
		m_selectedModel->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.0f, 0.0f }, { 0.6f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 0.3f*128.f));
	}
}

void CFramebuffersApplication::CreateShaders()
{
	m_shader = new CShader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
}

void CFramebuffersApplication::CreateLights()
{
	CLightsSet* lightsSet = new CLightsSet();

	CPointLight* light1 = new CPointLight();
	light1->SetPosition({ 0.f, 2.5f, -4.f});
	light1->SetAmbient({ 0.4f, 0.4f, 0.4f });
	light1->SetDiffuse({ 0.5f, 0.5f, 0.5f });
	light1->SetSpecular({ 1.0f, 1.0f, 1.0f });

	lightsSet->AddPointLight(light1);

	m_scene.SetLightsSet(lightsSet);
}

void CFramebuffersApplication::CreateScene()
{
	LoadScene();
	SelectNextModel();
}

void CFramebuffersApplication::LoadDefaultModel(CModel* model)
{
	dynamic_cast<CAssimpModel*>(model)->LoadModel("Data/models/plane.obj");
}

void CFramebuffersApplication::ConfigureModel(CModel* model)
{
	model->SetShader(m_shader);
}