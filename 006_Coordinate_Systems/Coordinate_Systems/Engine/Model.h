#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture;
class Mesh;
class Shader;

class Model
{
public:

	Model();
	Model(Shader* shader, Texture* texture, Mesh* mesh, glm::mat4* view, glm::mat4* projection);
	virtual ~Model() {}
	Model(const Model&) = delete;
	Model& operator=(Model const&) = delete;

	virtual void Update() {}
	virtual void Draw();

	glm::mat4 m_trans;

protected:
	virtual void BindUniforms();

	Shader* m_shader;
	Texture* m_texture;
	Mesh* m_mesh;
	glm::mat4 *m_view;
	glm::mat4 *m_projection;
};

