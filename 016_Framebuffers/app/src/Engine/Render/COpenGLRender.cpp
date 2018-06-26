#include <Engine/Render/COpenGLRender.h>

#include <Engine/Model/CMesh.h>
#include <Engine/Shader/CShader.h>

#include <glm/glm.hpp>

COpenGLRender::COpenGLRender()
{
	m_colorShader = new CShader("Data/Shaders/color2D.vert", "Data/Shaders/color2D.frag");
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
	m_colorShader->Use();

	glm::vec4 screenRect =
	{
		((rect[0]) / static_cast<float>(m_windowWidth))*2 - 1.f,
		((rect[1]) / static_cast<float>(m_windowHeight))*2 - 1.0f,
		((rect[2] ) / static_cast<float>(m_windowWidth))*2,
		((rect[3]) / static_cast<float>(m_windowHeight))*2,

	};

	float vertices[] = {
		// positions														//colors
		screenRect[0] + screenRect[2], screenRect[1],				  0.0f,	1.0f, 0.0f, 0.0f,	 // bottom right
		screenRect[0],				   screenRect[1],				  0.0f,	1.0f, 0.0f, 0.0f,	 // bottom left
		screenRect[0],				   screenRect[1] + screenRect[3], 0.0f,   1.0f, 0.0f, 0.0f   // top 
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}



