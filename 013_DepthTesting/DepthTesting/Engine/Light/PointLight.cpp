#include <Engine/Light/PointLight.h>

#include <Engine/Model/Mesh.h>
#include <Engine/Shader/Shader.h>
#include <Engine/Camera/Camera.h>
#include <Engine/Utils.h>

#include <glm/gtc/type_ptr.hpp>

PointLight::PointLight() : m_constantAttenuation(0.01f), m_linearAttenuation(0.01f), m_quadraticAttenuation(0.01f)
{
	CreateDebugDrawData();
}

void PointLight::SetAttenuation(float constant, float linear, float quadratic)
{
	m_constantAttenuation = constant;
	m_linearAttenuation = linear;
	m_quadraticAttenuation = quadratic;
}

void PointLight::DebugDraw(Camera& camera)
{
	m_debugShader->Use();
	BindUniformsDebug(*m_debugShader, camera);
	m_debugMesh->Draw(*m_debugShader);
}

void PointLight::Use(const Shader& shader, int count) const
{
	std::string countStr = std::to_string(count);

	shader.SetVec3("pointLights[" + countStr + "].position", GetPosition());
	shader.SetVec3("pointLights[" + countStr + "].ambient", GetAmbient());
	shader.SetVec3("pointLights[" + countStr + "].diffuse", GetDiffuse());
	shader.SetVec3("pointLights[" + countStr + "].specular", GetSpecular());

	shader.SetFloat("pointLights[" + countStr + "].constantAttenuation", m_constantAttenuation);
	shader.SetFloat("pointLights[" + countStr + "].linearAttenuation", m_linearAttenuation);
	shader.SetFloat("pointLights[" + countStr + "].quadraticAttenuation", m_quadraticAttenuation);
}

void PointLight::CreateDebugDrawData()
{
	float width = 0.25f;
	float height = 0.25f;
	float depth = 0.25f;

	std::vector<Vertex> vertices = {
		{ -width, -height,  depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ width, -height,  depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ width,  height,  depth, 0.f, 0.f, 0.f, 0.f, 0.f },
	{ -width,  height,  depth, 0.f, 0.f, 0.f, 0.f, 0.f },
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

void PointLight::BindUniformsDebug(const Shader& shader, const Camera& camera)
{
	shader.SetMat4("model", std::move(m_trans));
	shader.SetMat4("view", camera.GetViewMatrix());
	shader.SetMat4("projection", camera.GetProjectionMatrix());
	shader.SetVec3("color", GetDiffuse());
}