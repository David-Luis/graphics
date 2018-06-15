#include <CameraController.h>

#include <Engine/CCamera/CCamera.h>

#include <GLFW/glfw3.h>
#include <imgui.h>

CameraController::CameraController() : m_mouseEnabled(false)
{

}

void CameraController::SetCamera(CCamera* camera)
{
	m_camera = camera;
}

void CameraController::ProcessInput(GLFWwindow* window, glm::vec3 deltaMousePosition, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CameraMovement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CameraMovement::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CameraMovement::DOWN, deltaTime);

	if (glfwGetMouseButton(window, 0) == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse)
	{
		m_mouseEnabled = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_camera->ProcessMouseMovement(deltaMousePosition.x, deltaMousePosition.y);
	}
	else
	{
		m_mouseEnabled = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}