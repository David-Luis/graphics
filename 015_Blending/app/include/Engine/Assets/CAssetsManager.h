#pragma once

#include <unordered_map>

#include <string>

class Texture;

class CAssetsManager {

public:
	CAssetsManager() {}

	void LoadTexture(std::string path);
	Texture* GetTexture(std::string path);

private:
	std::unordered_map<std::string, Texture*> m_textures;
};