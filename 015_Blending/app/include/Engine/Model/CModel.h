#pragma once

#include <Engine/Model/IModel.h>

#include <Engine/SUniqueId.h>

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

	bool CModel::operator==(const CModel& model) const
	{
		return this->GetId() == model.GetId();
	}

	std::vector<CMesh*>& GetMeshes() { return m_meshes; }

	void Update() override {}
	void Draw(CCamera& camera, CLightsSet& lights) override;

	void SetShader(CShader* shader) { m_shader = shader; }
	CShader* GetShader() const { return m_shader; }
	
	void SetTransform(const glm::mat4& trans) { m_trans = trans; }
	glm::mat4 GetTransform() const { return m_trans; }

	void SetTransformComponents(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float angle);

	long long GetId() const { return m_id.GetId(); }

protected:
	virtual void BindUniforms();

	CShader* m_shader;
	std::vector<CMesh*> m_meshes; 
	glm::mat4 m_trans;

private:
	SUniqueId m_id;
};

