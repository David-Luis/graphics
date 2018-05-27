#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>
#include <vector>

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::vector<Model*> LoadModels();
Model* LoadModel1();
Model* LoadModel2();
void DrawModels(const std::vector<Model*>& models);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		assert(false);
		return -1;
	}

	std::vector<Model*> models = LoadModels();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		DrawModels(models);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

std::vector<Model*> LoadModels()
{
	std::vector<Model*> models;
	
	models.push_back(LoadModel1());
	models.push_back(LoadModel2());

	return models;
}

Model* LoadModel1()
{
	std::vector<float> vertices = {
		// positions		 // colors		   // texture coords
		-0.25f,  0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
		-0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
		-0.75f, -0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.75f,  0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // top left 
	};

	std::vector<unsigned int> indices = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	Shader* shader = new Shader("vertex_shader.vert", "fragment_shader.frag");
	Mesh* mesh = new Mesh(vertices, indices);
	Texture* texture = new Texture("wall.jpg");

	return new Model(shader, texture, mesh);
}

Model* LoadModel2()
{
	std::vector<float> vertices = {
		// positions		 // colors		   // texture coords
		0.25f,  0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		0.75f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		0.75f,  0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left 
	};

	std::vector<unsigned int> indices = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	Shader* shader = new Shader("vertex_shader.vert", "fragment_shader.frag");
	Mesh* mesh = new Mesh(vertices, indices);
	Texture* texture = new Texture("wall.jpg");

	return new Model(shader, texture, mesh);
}

void DrawModels(const std::vector<Model*>& models)
{
	for (const auto& model : models)
	{
		model->Update();
		model->Draw();
	}
}