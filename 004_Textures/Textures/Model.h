#pragma once

#include <glad/glad.h>

class Texture;
class Mesh;

class Model
{
public:

	Model();
	Model(GLuint shaderProgram, Texture* texture, Mesh* mesh);
	virtual ~Model() {}
	Model(const Model&) = delete;
	Model& operator=(Model const&) = delete;

	virtual void Update() {}
	virtual void Draw();

protected:
	virtual void BindUniforms() {}

	GLuint m_shaderProgram;
	Texture* m_texture;
	Mesh* m_mesh;
};

