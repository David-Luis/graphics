#pragma once

#include <Engine/OpenGLApplication.h>

#include <vector>

struct GLFWwindow;
class Camera;

class CameraController 
{
public:
	CameraController();
	void SetCamera(Camera* camera);
	void ProcessInput(GLFWwindow* window, glm::vec3 deltaMousePosition, float deltaTime);

private:
	Camera* m_camera;
	bool m_mouseEnabled;
};
