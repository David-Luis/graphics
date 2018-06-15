#pragma once

#include <Engine/Model/IModel.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class CMesh;
class CShader;
class CCCamera;
class CLightsSet;

class CModel : public IModel
{
public:
	CModel();
	CModel(std::vector<CMesh*>& meshes);
	
	virtual ~CModel();
	CModel(const CModel&) = delete;
	CModel& operator=(CModel const&) = delete;

	std::vector<CMesh*>& GetMeshes() { return m_meshes; }

	void Update() override {}
	void Draw(CShader& shader, CCamera& camera, CLightsSet& lights) override;

	void SetTransform(const glm::mat4& trans) { m_trans = trans; }
	glm::mat4 GetTransform() { return m_trans; }

	void SetTransformComponents(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float angle);

protected:
	virtual void BindUniforms(const CShader& shader);

	std::vector<CMesh*> m_meshes; 
	
	glm::mat4 m_trans;
};

