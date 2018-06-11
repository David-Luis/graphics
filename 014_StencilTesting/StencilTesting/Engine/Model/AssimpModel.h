#pragma once

#include <Engine/Model/Model.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
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

class AssimpModel : public Model
{
public:
	AssimpModel(std::string path);
	
	virtual ~AssimpModel();
	AssimpModel(const AssimpModel&) = delete;
	AssimpModel& operator=(AssimpModel const&) = delete;

protected:
	virtual void LoadModel(std::string path);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::string m_directory;
};

