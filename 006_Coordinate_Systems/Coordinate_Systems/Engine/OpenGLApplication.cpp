#include <Engine/OpenGLApplication.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <assert.h>
#include <vector>

OpenGLApplication::OpenGLApplication(unsigned int windowsWidth, unsigned int windowsHeight, std::string windowTitle)
	: m_windowsWidth(windowsWidth)
	, m_windowsHeight(windowsHeight)
	, m_windowTitle(windowTitle)
{

}

void OpenGLApplication::Init()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	m_window = glfwCreateWindow(m_windowsWidth, m_windowsHeight, m_windowTitle.c_str(), NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_window);

	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
		OpenGLApplication* pw = static_cast<OpenGLApplication*>(glfwGetWindowUserPointer(window));
		pw->OnWindowResize(width, height);
	});

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		assert(false);
		return;
	}

	OnInit();

	while (!glfwWindowShouldClose(m_window))
	{
		GameLoop();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void OpenGLApplication::Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	OnDraw();
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void OpenGLApplication::GameLoop()
{
	ProcessInput(m_window);
	OnUpdate();
	Draw();
}

void OpenGLApplication::ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGLApplication::OnWindowResize(int width, int height)
{
	glViewport(0, 0, width, height);
}