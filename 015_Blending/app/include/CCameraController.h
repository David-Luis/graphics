#pragma once

#include <Engine/OpenGLApplication.h>

#include <vector>

struct GLFWwindow;
class CCamera;

class CameraController 
{
public:
	CameraController();
	void SetCamera(CCamera* camera);
	void ProcessInput(GLFWwindow* window, glm::vec3 deltaMousePosition, float deltaTime);

private:
	CCamera* m_camera;
	bool m_mouseEnabled;
};
