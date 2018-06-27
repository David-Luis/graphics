#pragma once

#include <Engine/Texture/CTexture.h>

#include <glad/glad.h>

class CFramebuffer
{
public:
	CFramebuffer() {}

	void Init(GLuint width, GLuint height);
	void Use();

	CTexture* GetAsTexture() const;

private:
	GLuint m_id;
	GLuint m_textureColorbuffer;

	CTexture* m_texture;
};
