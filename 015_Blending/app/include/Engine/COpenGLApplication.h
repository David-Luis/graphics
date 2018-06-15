#pragma once

#include <Engine/CCamera/CCamera.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

struct GLFWwindow;

class OpenGLApplication
{
public:
	OpenGLApplication(unsigned int windowsWidth, unsigned int windowsHeight, std::string windowTitle);
	virtual ~OpenGLApplication() {}
	OpenGLApplication(const OpenGLApplication&) = delete;
	OpenGLApplication& operator=(OpenGLApplication const&) = delete;

	void Init();

protected:
	virtual void ProcessInput();
	virtual void OnWindowResize(int width, int height);
	virtual void OnInit() {}
	virtual void OnDraw() {}
	virtual void OnUpdate() {}

	GLFWwindow * m_window;

	unsigned int m_windowsWidth;
	unsigned int m_windowsHeight;
	CCamera m_camera;

	//TODO: Move all the code to input the camera to another class
	glm::vec3 m_mousePosition;
	glm::vec3 m_deltaMousePosition;
	glm::vec3 m_lastMousePosition;

	float m_deltaTime;

private:
	void InitImgui();
	void GameLoop();
	void Draw();
	void OnMouseMove(double xpos, double ypos);

	float m_lastTime;
	std::string m_windowTitle;

};
