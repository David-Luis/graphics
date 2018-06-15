#include <Engine/Light/SpotLight.h>

#include <Engine/Model/Mesh.h>
#include <Engine/Shader/Shader.h>
#include <Engine/CCamera/CCamera.h>
#include <Engine/Utils.h>

#include <glm/gtc/type_ptr.hpp>

SpotLight::SpotLight() : m_direction(0.f, 0.f, -1.f), m_constantAttenuation(0.01f), m_linearAttenuation(0.01f), m_quadraticAttenuation(0.01f)
{
	CreateDebugDrawData();
}

void SpotLight::SetAttenuation(float constant, float linear, float quadratic)
{
	m_constantAttenuation = constant;
	m_linearAttenuation = linear;
	m_quadraticAttenuation = quadratic;
}

void SpotLight::SetCutoff(float cutOff, float outerCutOff)
{
	m_cutOff = cutOff;
	m_outerCutOff = outerCutOff;
}

void SpotLight::SetDirection(const glm::vec3& direction)
{
	m_direction = direction;
	m_trans = glm::inverse(glm::lookAt(m_position, m_position + m_direction, glm::vec3(0.f, 1.f, 0.f)));
}

glm::vec3 SpotLight::GetDirection() const
{
	return m_direction;
}

void SpotLight::DebugDraw(CCamera& camera)
{
	m_debugShader->Use();
	BindUniformsDebug(*m_debugShader, camera);
	m_debugMesh->Draw(*m_debugShader);
}

void SpotLight::Use(const Shader& shader, int count) const
{
	std::string countStr = std::to_string(count);
	shader.SetVec3("spotLights[" + countStr + "].position", GetPosition());
	shader.SetVec3("spotLights[" + countStr + "].direction", GetDirection());
	shader.SetVec3("spotLights[" + countStr + "].ambient", GetAmbient());
	shader.SetVec3("spotLights[" + countStr + "].diffuse", GetDiffuse());
	shader.SetVec3("spotLights[" + countStr + "].specular", GetSpecular());

	shader.SetFloat("spotLights[" + countStr + "].constantAttenuation", m_constantAttenuation);
	shader.SetFloat("spotLights[" + countStr + "].linearAttenuation", m_linearAttenuation);
	shader.SetFloat("spotLights[" + countStr + "].quadraticAttenuation", m_quadraticAttenuation);

	shader.SetFloat("spotLights[" + countStr + "].cutOff", glm::cos(glm::radians(m_cutOff)));
	shader.SetFloat("spotLights[" + countStr + "].outerCutOff", glm::cos(glm::radians(m_outerCutOff)));
}

void SpotLight::CreateDebugDrawData()
{
	float width = 0.25f;
	float height = 0.25f;
	float depth = 0.25f;

	std::vector<Vertex> vertices = {
		{ -width*0.1f, -height*0.1f,  depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ width*0.1f, -height*0.1f,  depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ width*0.1f,  height*0.1f,  depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ -width*0.1f,  height*0.1f,  depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	// back
	{ -width, -height, -depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ width, -height, -depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ width,  height, -depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ -width,  height, -depth, 0.f, 0.f, 0.f, 0.f, 0.f }
	};

	std::vector<GLuint> indices = {
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

	std::vector<Texture*> textures = {};
	m_debugMesh = new Mesh(vertices, indices, textures);

	m_debugShader = new Shader("Data/Shaders/shader_debug_light.vert", "Data/Shaders/shader_debug_light.frag");
}

void SpotLight::BindUniformsDebug(const Shader& shader, const CCamera& camera)
{
	GLuint transformLoc = glGetUniformLocation(shader.GetId(), "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(m_trans));

	GLuint viewLoc = glGetUniformLocation(shader.GetId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

	GLuint projecttionLoc = glGetUniformLocation(shader.GetId(), "projection");
	glUniformMatrix4fv(projecttionLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjectionMatrix()));
}