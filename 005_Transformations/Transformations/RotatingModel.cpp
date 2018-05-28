#include <RotatingModel.h>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

RotatingModel::RotatingModel(Shader* shader, Texture* texture, Mesh* mesh, float speed) : Model(shader, texture, mesh), m_speed(speed)
{

}

void RotatingModel::Update()
{
	m_trans = glm::mat4();
	m_trans = glm::rotate(m_trans, (float)(glfwGetTime()) * m_speed, glm::vec3(0.0f, 0.0f, 1.0f));
}