#pragma once

#include <unordered_map>

#include <string>

class Texture;

class AssetsManager {

public:
	AssetsManager() {}

	void LoadTexture(std::string path);
	Texture* GetTexture(std::string path);

private:
	std::unordered_map<std::string, Texture*> m_textures;
};