#pragma once

#include <vector>

class CTexture;
class CShader;

class CTextureSet {

public:
	CTextureSet() {}
	CTextureSet(std::vector<CTexture*>);
	
	void AddTexture(CTexture* texture) { m_textures.push_back(texture); }
	void Use(const CShader& shader) const;

private:
	std::vector<CTexture*> m_textures;
};