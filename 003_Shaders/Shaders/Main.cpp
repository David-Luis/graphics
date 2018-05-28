#include "ShaderUtils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>
#include <vector>

class Model
{
public:
	Model() : m_shaderProgram(0), m_VAO(0), m_VBO(0), m_EBO(0)
	{

	}

	Model(GLuint shaderProgram, GLuint VAO, GLuint VBO, GLuint EBO) : m_shaderProgram(shaderProgram), m_VAO(VAO), m_VBO(VBO), m_EBO(EBO)
	{

	}

	GLuint m_shaderProgram;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;

	virtual void Update()
	{

	}

	virtual void BindUniforms()
	{

	}

	void Draw()
	{
		glUseProgram(m_shaderProgram);
		glBindVertexArray(m_VAO);
		BindUniforms();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};

class Model1 : public Model
{
public:
	Model1(GLuint shaderProgram, GLuint VAO, GLuint VBO, GLuint EBO) : Model(shaderProgram, VAO, VBO, EBO)
	{

	}

	Model1(const Model1&) = delete;
	Model1& operator= (const Model1&) = delete;

	void BindUniforms() override
	{
		glUniform4f(m_vertexColorLocation, 0.0f, m_greenValue, 0.0f, 1.0f);
	}

	void Update() override
	{
		float timeValue = static_cast<float>(glfwGetTime());
		m_greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		m_vertexColorLocation = glGetUniformLocation(m_shaderProgram, "ourColor");
	}

private:
	float m_greenValue;
	GLuint m_vertexColorLocation;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLuint CreateVertexShader(std::string shaderPath);
GLuint CreateFragmentShader(std::string shaderPath);
GLuint LinkShaders(int vertexShader, int fragmentShader);
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shaders", NULL, NULL);
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


GLuint CreateVertexShader(std::string shaderPath)
{
	std::string shader = ShaderUtils::LoadShaderFile(shaderPath);
	const GLchar* const shaderChar = shader.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderChar, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		assert(false);
	}

	return vertexShader;
}

GLuint CreateFragmentShader(std::string shaderPath)
{
	std::string shader = ShaderUtils::LoadShaderFile(shaderPath);
	const GLchar* const shaderChar = shader.c_str();

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderChar, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		assert(false);
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return fragmentShader;
}

GLuint LinkShaders(int vertexShader, int fragmentShader)
{
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
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
	float vertices[] = {
		-0.25f,  0.25f, 0.0f,  // top right
		-0.25f, -0.25f, 0.0f,  // bottom right
		-0.75f, -0.25f, 0.0f,  // bottom left
		-0.75f,  0.25f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	GLuint vertexShader = CreateVertexShader("vertex_shader.vert");
	GLuint fragmentShader = CreateFragmentShader("fragment_shader.frag");
	GLuint shaderProgram = LinkShaders(vertexShader, fragmentShader);

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return new Model1(shaderProgram, VAO, VBO, EBO);
}

Model* LoadModel2()
{
	float vertices[] = {
		// positions		  // colors
		0.25f,  0.25f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
		0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		0.75f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
		0.75f,  0.25f, 0.0f, 1.0f, 1.0f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	GLuint vertexShader = CreateVertexShader("vertex_shader_2.vert");
	GLuint fragmentShader = CreateFragmentShader("fragment_shader_2.frag");
	GLuint shaderProgram = LinkShaders(vertexShader, fragmentShader);

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return new Model(shaderProgram, VAO, VBO, EBO);
}

void DrawModels(const std::vector<Model*>& models)
{
	for (const auto& model : models)
	{
		model->Update();
		model->Draw();
	}
}