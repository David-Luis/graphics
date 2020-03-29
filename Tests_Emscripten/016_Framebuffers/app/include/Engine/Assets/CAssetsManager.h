#pragma once

#include <unordered_map>

#include <string>

class CTexture;

class CAssetsManager {

public:
	CAssetsManager() {}

	void LoadTexture(std::string path);
	CTexture* GetTexture(std::string path);

private:
	std::unordered_map<std::string, CTexture*> m_textures;
};