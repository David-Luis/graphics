#pragma once

#include <Engine/Render/IRender.h>

#include <glad/glad.h>

#include <vector>

class CShader;

class COpenGLRender : public IRender
{
public:
	COpenGLRender();

	void SetWindowSize(GLuint width, GLuint height);

	void DrawMesh(const CMesh* mesh, const CShader& shader) const override;
	void DrawMesh(const CMesh* mesh, const CShader& shader, const CTextureSet& textureSet) const override;
	void DrawMesh(const CMesh* mesh, const CShader& shader, const CTextureSet& textureSet, const CMaterial& material) const override;

	void Draw2DQuad(glm::vec4 rect, glm::vec4 color) const override;

private:
	void DrawVAO(GLuint VAO, std::size_t indexCount) const;

	GLuint m_windowWidth;
	GLuint m_windowHeight;
	CShader* m_colorShader;
};
