#pragma once

#include <Engine/IModel.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Mesh;

class Model : public IModel
{
public:
	Model() {}
	Model(std::vector<Mesh*>& meshes);
	
	virtual ~Model();
	Model(const Model&) = delete;
	Model& operator=(Model const&) = delete;

	void Update() override {}
	void Draw(Shader& shader, Camera& camera) override;

	void SetTransform(const glm::mat4& trans) { m_trans = trans; }
	const glm::mat4& GetTransform() { return m_trans; }

protected:
	virtual void BindUniforms(const Shader& shader, const Camera& camera);

	std::vector<Mesh*> m_meshes; 
	glm::mat4 m_trans;
};

