#include <Engine/Light/PointLight.h>

#include <Engine/Model/Mesh.h>
#include <Engine/Shader/Shader.h>
#include <Engine/Camera/Camera.h>
#include <Engine/Utils.h>

#include <glm/gtc/type_ptr.hpp>

PointLight::PointLight()
{
	CreateDebugDrawData();
}

void PointLight::DebugDraw(Camera& camera)
{
	m_debugShader->Use();
	BindUniformsDebug(*m_debugShader, camera);
	m_debugMesh->Draw(*m_debugShader);
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

	m_debugShader = new Shader("Data/Shaders/shader_debug_point_light.vert", "Data/Shaders/shader_debug_point_light.frag");
}

void PointLight::BindUniformsDebug(const Shader& shader, const Camera& camera)
{
	GLuint transformLoc = glGetUniformLocation(shader.GetId(), "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(m_trans));

	GLuint viewLoc = glGetUniformLocation(shader.GetId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

	GLuint projecttionLoc = glGetUniformLocation(shader.GetId(), "projection");
	glUniformMatrix4fv(projecttionLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjectionMatrix()));
}