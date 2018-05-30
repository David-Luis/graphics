#pragma once

#include <glad/glad.h>

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

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;
struct Texture;

class Model
{
public:

	Model(std::string path);
	Model(std::vector<Mesh*>& meshes);
	
	virtual ~Model();
	Model(const Model&) = delete;
	Model& operator=(Model const&) = delete;

	virtual void Update() {}
	virtual void Draw(Shader& shader, Camera& camera);

	glm::mat4 m_trans;

protected:
	virtual void LoadModel(std::string path);
	virtual void BindUniforms(const Shader& shader, const Camera& camera);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLuint TextureFromFile(const char *path, const std::string &directory);

	std::vector<Mesh*> m_meshes;
	std::string m_directory;
};

