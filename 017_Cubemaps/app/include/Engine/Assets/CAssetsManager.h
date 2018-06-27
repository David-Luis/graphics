#pragma once

#include <unordered_map>

#include <string>

class CTexture;

class CAssetsManager {

public:
	CAssetsManager() {}

	CTexture* LoadTexture(std::string path);

private:
	CTexture* GetTexture(std::string path);

	std::unordered_map<std::string, CTexture*> m_textures;
};