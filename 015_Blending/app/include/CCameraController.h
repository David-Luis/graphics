#pragma once

#include <Engine/COpenGLApplication.h>

#include <vector>

struct GLFWwindow;
class CCamera;

class CCameraController 
{
public:
	CCameraController();
	void SetCamera(CCamera* camera);
	void ProcessInput(GLFWwindow* window, glm::vec3 deltaMousePosition, float deltaTime);

private:
	CCamera* m_camera;
	bool m_mouseEnabled;
};
