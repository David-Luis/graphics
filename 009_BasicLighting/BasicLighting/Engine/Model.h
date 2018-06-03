#pragma once

#include <Engine/IModel.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Mesh;
class Shader;
class Camera;

class Model : public IModel
{
public:
	Model();
	Model(std::vector<Mesh*>& meshes);
	
	virtual ~Model();
	Model(const Model&) = delete;
	Model& operator=(Model const&) = delete;

	void Update() override {}
	void Draw(Shader& shader, Camera& camera) override;

	void SetTransform(const glm::mat4& trans) { m_trans = trans; }
	glm::mat4 GetTransform() { return m_trans; }

	void SetColor(const glm::vec3& color) { m_color = color; }
	glm::vec3 GetColor() { return m_color; }

protected:
	virtual void BindUniforms(const Shader& shader, const Camera& camera);

	std::vector<Mesh*> m_meshes; 
	glm::mat4 m_trans;
	glm::vec3 m_color;
};

