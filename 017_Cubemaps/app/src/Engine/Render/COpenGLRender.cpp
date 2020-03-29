#include <Engine/Render/COpenGLRender.h>

#include <Engine/Model/CMesh.h>
#include <Engine/Shader/CShader.h>
#include <Engine/Render/CFramebuffer.h>
#include <Engine/Texture/CTextureCubemap.h>
#include <Engine/Camera/CCamera.h>

#include <glm/glm.hpp>

COpenGLRender::COpenGLRender()
{
	m_skyboxShader = new CShader("Data/Shaders/skybox.vert", "Data/Shaders/skybox.frag");
	m_colorShader2D = new CShader("Data/Shaders/color2D.vert", "Data/Shaders/color2D.frag");
	m_textureShader2D = new CShader("Data/Shaders/texture2D.vert", "Data/Shaders/texture2D.frag");
}

void COpenGLRender::SetWindowSize(GLuint width, GLuint height)
{
	m_windowWidth = width;
	m_windowHeight = height;
}

void COpenGLRender::DrawMesh(const CMesh* mesh, const CShader& shader) const
{
	mesh->GetMaterial().Use(shader);
	mesh->GetTextures().Use(shader);
	DrawVAO(mesh->GetVAO(), mesh->GetIndices().size());
	glActiveTexture(GL_TEXTURE0);
}


void COpenGLRender::DrawMesh(const CMesh* mesh, const CShader& shader, const CTextureSet& textureSet) const
{
	mesh->GetMaterial().Use(shader);
	textureSet.Use(shader);
	DrawVAO(mesh->GetVAO(), mesh->GetIndices().size());
	glActiveTexture(GL_TEXTURE0);
}

void COpenGLRender::DrawMesh(const CMesh* mesh, const CShader& shader, const CTextureSet& textureSet, const CMaterial& material) const
{
	material.Use(shader);
	textureSet.Use(shader);
	DrawVAO(mesh->GetVAO(), mesh->GetIndices().size());
	glActiveTexture(GL_TEXTURE0);
}

void COpenGLRender::DrawVAO(GLuint VAO, std::size_t indexCount) const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void COpenGLRender::Draw2DQuad(glm::vec4 rect, glm::vec4 color) const
{
	m_colorShader2D->Use();

	glm::vec4 screenRect =
	{
		((rect[0]) / static_cast<float>(m_windowWidth))*2 - 1.f,
		((rect[1]) / static_cast<float>(m_windowHeight))*2 - 1.0f,
		((rect[2] ) / static_cast<float>(m_windowWidth))*2,
		((rect[3]) / static_cast<float>(m_windowHeight))*2,

	};

	float vertices[] = {
		// positions														//colors
		screenRect[0] + screenRect[2], screenRect[1],				  0.0f,	color.r, color.g, color.b, color.a, // bottom right
		screenRect[0],				   screenRect[1],				  0.0f,	color.r, color.g, color.b, color.a, // bottom left
		screenRect[0],				   screenRect[1] + screenRect[3], 0.0f, color.r, color.g, color.b, color.a, // top left
		screenRect[0] + screenRect[2], screenRect[1],				  0.0f,	color.r, color.g, color.b, color.a, // bottom right
		screenRect[0],				   screenRect[1] + screenRect[3], 0.0f, color.r, color.g, color.b, color.a, // top left
		screenRect[0] + screenRect[2], screenRect[1] + screenRect[3], 0.0f, color.r, color.g, color.b,  color.a  // top right
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void COpenGLRender::Draw2DQuad(glm::vec4 rect, const CTextureSet& textureSet, glm::vec4 color) const
{
	Draw2DQuad(rect, textureSet, color, *m_textureShader2D);
}

void COpenGLRender::Draw2DQuad(glm::vec4 rect, const CTextureSet& textureSet, glm::vec4 color, const CShader& shader) const
{
	shader.Use();
	textureSet.Use(*m_textureShader2D);

	glm::vec4 screenRect =
	{
		((rect[0]) / static_cast<float>(m_windowWidth)) * 2 - 1.f,
		((rect[1]) / static_cast<float>(m_windowHeight)) * 2 - 1.0f,
		((rect[2]) / static_cast<float>(m_windowWidth)) * 2,
		((rect[3]) / static_cast<float>(m_windowHeight)) * 2,

	};

	float vertices[] = {
		// positions														//colors
		screenRect[0] + screenRect[2], screenRect[1],				  0.0f,	color.r, color.g, color.b, color.a, 1.f, 0.f, // bottom right
		screenRect[0],				   screenRect[1],				  0.0f,	color.r, color.g, color.b, color.a, 0.f, 0.f, // bottom left
		screenRect[0],				   screenRect[1] + screenRect[3], 0.0f, color.r, color.g, color.b, color.a, 0.f, 1.f, // top left
		screenRect[0] + screenRect[2], screenRect[1],				  0.0f,	color.r, color.g, color.b, color.a, 1.f, 0.f, // bottom right
		screenRect[0],				   screenRect[1] + screenRect[3], 0.0f, color.r, color.g, color.b, color.a, 0.f, 1.f, // top left
		screenRect[0] + screenRect[2], screenRect[1] + screenRect[3], 0.0f, color.r, color.g, color.b, color.a, 1.f, 1.f, // top right
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void COpenGLRender::DrawSkybox(const CTextureCubemap& cubemap, const CCamera& camera) const
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	glDepthMask(GL_FALSE);
	m_skyboxShader->Use();
	camera.UseForSkybox(*m_skyboxShader);

	// skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(skyboxVAO);
	cubemap.Use(*m_skyboxShader, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}

void COpenGLRender::DrawFramebuffer(const CFramebuffer& framebuffer, glm::vec4 rect, const CShader& shader) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); 
	Draw2DQuad(rect, CTextureSet({framebuffer.GetAsTexture()}), glm::vec4(1.f), shader);
}



