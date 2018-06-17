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

CBlendingApplication::CBlendingApplication() : COpenGLApplication(1500, 720, "BLENDING")
	, m_shader(nullptr)
	, m_selectedModel(nullptr)
	, m_controlPressed(false)
	, m_altPressed(false)
	, m_enterPressed(false)
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

	ProcessInputEditorCreateModel();
	ProcessInputIterateModel();
	ProcessInputEditorMoveModel();
	ProcessInputEditorRotateModel();
	ProcessInputEditorScaleModel();
	ProcessInputSaveLoadScene();
}

void CBlendingApplication::ProcessInputEditorCreateModel()
{
	if ((glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) && !m_spacePressed)
	{
		m_spacePressed = true;
		if (m_selectedModel)
		{
			m_selectedModel->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.1f, 0.1f }, { 0.6f, 0.6f, 0.6f }, { 1.0f, 1.0f, 1.0f }, 0.3f*128.f));
		}

		m_selectedModel = LoadModel({ 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, "Data/models/cube.obj");
		m_selectedModel->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.0f, 0.0f }, { 0.6f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 0.3f*128.f));
	}

	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		m_spacePressed = false;
	}
}

void CBlendingApplication::ProcessInputIterateModel()
{
	if ((glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS) && !m_enterPressed && m_selectedModel)
	{
		m_enterPressed = true;

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

		m_selectedModel = models[i%models.size()];
		m_selectedModel->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.0f, 0.0f }, { 0.6f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 0.3f*128.f));
	}

	if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_RELEASE)
	{
		m_enterPressed = false;
	}
}

void CBlendingApplication::ProcessInputEditorMoveModel()
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

void CBlendingApplication::ProcessInputEditorRotateModel()
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

void CBlendingApplication::ProcessInputEditorScaleModel()
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

void CBlendingApplication::ProcessInputSaveLoadScene()
{
	if ((glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_PRESS) && !m_savePressed)
	{
		m_savePressed = true;

		std::ofstream sceneFile;
		sceneFile.open("Data/scene1");
		sceneFile << m_scene << std::endl;
		sceneFile.close();
	}

	if (glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_RELEASE)
	{
		m_savePressed = false;
	}
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
	m_selectedModel = LoadModel({ 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, "Data/models/cube.obj");
	m_selectedModel->GetMeshes()[0]->SetMaterial(CMaterial({ 0.1f, 0.0f, 0.0f }, { 0.6f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 0.3f*128.f));
}

CModel* CBlendingApplication::LoadModel(glm::vec3 position, glm::vec3 scale, std::string modelPath)
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

	return model;
}