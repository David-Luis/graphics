#include <TransformationsApplication.h>

#include <RotatingModel.h>

#include <Engine/Mesh.h>
#include <Engine/Texture.h>
#include <Engine/Shader.h>
#include <Engine/Model.h>

TransformationsApplication::TransformationsApplication() : OpenGLApplication(800, 600, "Transformations")
{

}

void TransformationsApplication::OnInit()
{
	LoadModels();
}

void TransformationsApplication::OnDraw()
{
	DrawModels();
}

void TransformationsApplication::LoadModels()
{
	m_models.push_back(LoadModel1());
	m_models.push_back(LoadModel2());
}

Model* TransformationsApplication::LoadModel1()
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

	Shader* shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
	Mesh* mesh = new Mesh(vertices, indices);
	Texture* texture = new Texture("Data/Textures/wall.jpg");

	return new RotatingModel(shader, texture, mesh, 2.0f);
}

Model* TransformationsApplication::LoadModel2()
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

	Shader* shader = new Shader("Data/Shaders/shader.vert", "Data/Shaders/shader.frag");
	Mesh* mesh = new Mesh(vertices, indices);
	Texture* texture = new Texture("Data/Textures/wall.jpg");

	return new RotatingModel(shader, texture, mesh, -2.0f);
}

void TransformationsApplication::DrawModels()
{
	for (const auto& model : m_models)
	{
		model->Update();
		model->Draw();
	}
}