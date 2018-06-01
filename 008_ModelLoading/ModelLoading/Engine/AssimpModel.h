#pragma once

#include <Engine/IModel.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>

#include <string>
#include <vector>

class Mesh;
class Shader;
class Camera;
class Texture;

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

class AssimpModel : public IModel
{
public:

	AssimpModel(std::string path);
	AssimpModel(std::vector<Mesh*>& meshes);
	
	virtual ~AssimpModel();
	AssimpModel(const AssimpModel&) = delete;
	AssimpModel& operator=(AssimpModel const&) = delete;

	void Update() override {}
	void Draw(Shader& shader, Camera& camera) override;

	glm::mat4 m_trans;

protected:
	virtual void LoadModel(std::string path);
	virtual void BindUniforms(const Shader& shader, const Camera& camera);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::vector<Mesh*> m_meshes;
	std::string m_directory;
};

