#pragma once

#include <Engine/Texture/CTexture.h>

#include <vector>
#include <string>

class CShader;

class CTextureCubemap : public CTexture {

public:
	CTextureCubemap() {}
	CTextureCubemap(const CTextureCubemap&) = delete;
	CTextureCubemap& operator=(CTextureCubemap const&) = delete;
	
	void LoadFromFile(const std::string &filePath) override;
	void Use(const CShader& shader, GLuint index) const override;

private:
	std::vector<std::string> GetFacesFromPath(std::string path);
};