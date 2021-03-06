#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

class CMesh;
class CShader;
class CTextureSet;
class CMaterial;
class CFramebuffer;

class IRender
{
public:
	virtual void SetWindowSize(GLuint width, GLuint height) = 0;

	virtual void DrawMesh(const CMesh* mesh, const CShader& shader) const = 0; 
	virtual void DrawMesh(const CMesh* mesh, const CShader& shader, const CTextureSet& textureSet) const = 0;
	virtual void DrawMesh(const CMesh* mesh, const CShader& shader, const CTextureSet& textureSet, const CMaterial& material) const = 0;

	virtual void Draw2DQuad(glm::vec4 rect, glm::vec4 color) const = 0;
	virtual void Draw2DQuad(glm::vec4 rect, const CTextureSet& textureSet, glm::vec4 color) const = 0;
	virtual void Draw2DQuad(glm::vec4 rect, const CTextureSet& textureSet, glm::vec4 color, const CShader& shader) const = 0;

	virtual void DrawFramebuffer(const CFramebuffer& framebuffer, glm::vec4 rect, const CShader& shader) const = 0;
};
