#pragma once

#include <Engine/Model/IModel.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Mesh;
class Shader;
class CCamera;
class LightsSet;

class Model : public IModel
{
public:
	Model();
	Model(std::vector<Mesh*>& meshes);
	
	virtual ~Model();
	Model(const Model&) = delete;
	Model& operator=(Model const&) = delete;

	std::vector<Mesh*>& GetMeshes() { return m_meshes; }

	void Update() override {}
	void Draw(Shader& shader, CCamera& camera, LightsSet& lights) override;

	void SetTransform(const glm::mat4& trans) { m_trans = trans; }
	glm::mat4 GetTransform() { return m_trans; }

	void SetTransformComponents(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float angle);

protected:
	virtual void BindUniforms(const Shader& shader);

	std::vector<Mesh*> m_meshes; 
	
	glm::mat4 m_trans;
};

