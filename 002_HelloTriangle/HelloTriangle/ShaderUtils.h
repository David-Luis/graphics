#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>

namespace ShaderUtils
{
	static std::string LoadShaderFile(std::string filePath)
	{
		std::string content;
		std::ifstream fileStream(filePath, std::ios::in);

		if (!fileStream.is_open()) {
			assert(fileStream.is_open());
			return "";
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;
	}
};
