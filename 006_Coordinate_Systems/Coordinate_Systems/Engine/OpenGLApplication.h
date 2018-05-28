#pragma once

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
	virtual void ProcessInput(GLFWwindow *window);
	virtual void OnWindowResize(int width, int height);
	virtual void OnInit() {}
	virtual void OnDraw() {}
	virtual void OnUpdate() {}

	glm::mat4 m_view;
	glm::mat4 m_projection;
	unsigned int m_windowsWidth;
	unsigned int m_windowsHeight;

private:
	void InitImgui();
	void GameLoop();
	void Draw();

	GLFWwindow * m_window;

	std::string m_windowTitle;
};
