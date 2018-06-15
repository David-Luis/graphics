#pragma once

#include <Engine/Model/CModel.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>

#include <string>
#include <vector>

class CMesh;
class CShader;
class CCamera;
class CTexture;

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

class CAssimpModel : public CModel
{
public:
	CAssimpModel(std::string path);
	
	virtual ~CAssimpModel();
	CAssimpModel(const CAssimpModel&) = delete;
	CAssimpModel& operator=(CAssimpModel const&) = delete;

protected:
	virtual void LoadModel(std::string path);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	CMesh* ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<CTexture*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::string m_directory;
};

