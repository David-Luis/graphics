#include <Engine/COpenGLApplication.h>

#include <Engine/Engine.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include <iostream>
#include <assert.h>
#include <vector>

static void glfw_error_callback(int error, const char* description)
{
	std::cerr << "ERROR " << description;
}

COpenGLApplication::COpenGLApplication(unsigned int windowsWidth, unsigned int windowsHeight, std::string windowTitle)
	: m_windowsWidth(windowsWidth)
	, m_windowsHeight(windowsHeight)
	, m_camera(windowsWidth, windowsHeight)
	, m_windowTitle(windowTitle)
	, m_deltaTime(0)
	, m_lastTime(0)
{

}

void COpenGLApplication::Init()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwSetErrorCallback(glfw_error_callback);
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
		COpenGLApplication* pw = static_cast<COpenGLApplication*>(glfwGetWindowUserPointer(window));
		pw->OnWindowResize(width, height);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
		COpenGLApplication* pw = static_cast<COpenGLApplication*>(glfwGetWindowUserPointer(window));
		pw->OnMouseMove(x, y);
	});

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		assert(false);
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	InitImgui();

	OnInit();

	while (!glfwWindowShouldClose(m_window))
	{
		GameLoop();
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void COpenGLApplication::InitImgui()
{
	//check https://github.com/ocornut/imgui/blob/master/examples/opengl3_example/main.cpp
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	ImGui_ImplGlfwGL3_Init(m_window, true);

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
}

void COpenGLApplication::Draw()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	m_deltaTime = currentFrame - m_lastTime;
	m_lastTime = currentFrame;

	ImGui_ImplGlfwGL3_NewFrame();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	OnDraw();
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void COpenGLApplication::OnMouseMove(double xpos, double ypos)
{
	m_mousePosition.x = static_cast<float>(xpos);
	m_mousePosition.y = static_cast<float>(ypos);
	m_deltaMousePosition.x = m_mousePosition.x - m_lastMousePosition.x;
	m_deltaMousePosition.y = m_mousePosition.y - m_lastMousePosition.y;
	m_lastMousePosition = m_mousePosition;
}

void COpenGLApplication::GameLoop()
{
	ProcessInput();
	m_deltaMousePosition.x = m_mousePosition.x - m_lastMousePosition.x;
	m_deltaMousePosition.y = m_mousePosition.y - m_lastMousePosition.y;
	m_lastMousePosition = m_mousePosition;

	OnUpdate();
	Draw();	
}

void COpenGLApplication::ProcessInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}

void COpenGLApplication::OnWindowResize(int width, int height)
{
	glViewport(0, 0, width, height);
	m_camera.UpdateWindowsSize(width, height);
}