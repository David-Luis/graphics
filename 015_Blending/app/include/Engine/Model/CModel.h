#pragma once

#include <Engine/Model/IModel.h>

#include <Engine/SUniqueId.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

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
	
	void SetTransform(const glm::mat4& trans) { m_transform = trans; }
	glm::mat4 GetTransform() const { return m_transform; }

	void SetTranslation(glm::vec3 translation);
	void Translate(glm::vec3 translation);
	glm::vec3 GetTranslation() { return m_translation; }

	void SetRotation(glm::quat rotation);
	void SetRotation(float angle, glm::vec3 axis);
	void Rotate(glm::quat rotation);
	void Rotate(float angle, glm::vec3 axis);
	glm::quat GetRotation() { return m_rotation; }

	void SetScale(glm::vec3 scale);
	void Scale(glm::vec3 scale);
	glm::vec3 GetScale() { return m_scale; }

	long long GetId() const { return m_id.GetId(); }

protected:
	virtual void CalculateTransformation();
	virtual void BindUniforms();

	CShader* m_shader;
	std::vector<CMesh*> m_meshes; 

	glm::vec3 m_translation;
	glm::mat4 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_transform;

private:
	SUniqueId m_id;
};

