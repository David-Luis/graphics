#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture;
class Mesh;
class Shader;
class Camera;

class Model
{
public:

	Model();
	Model(Shader* shader, Texture* texture, Mesh* mesh);
	virtual ~Model() {}
	Model(const Model&) = delete;
	Model& operator=(Model const&) = delete;

	virtual void Update() {}
	virtual void Draw(Camera* m_camera);

	glm::mat4 m_trans;

protected:
	virtual void BindUniforms(Camera* m_camera);

	Shader* m_shader;
	Texture* m_texture;
	Mesh* m_mesh;
};

