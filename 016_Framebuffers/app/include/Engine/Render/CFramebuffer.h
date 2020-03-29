#pragma once

#include <Engine/Texture/CTextureSet.h>

#include <glad/glad.h>

class CFramebuffer
{
public:
	CFramebuffer() {}

	void Init(GLuint width, GLuint height);
	void Use();

	CTextureSet GetAsTextureSet() const;

private:
	GLuint m_id;
	GLuint m_textureColorbuffer;

	CTextureSet m_textureSet;
};
