#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Lib/json.hpp>

#include <string>

namespace SerializationUtils
{
	static std::string SerializeVec3(const glm::vec3 vec3)
	{
		std::vector<float> vector = { vec3.x, vec3.y, vec3.z };
		return nlohmann::json(vector).dump();
	}

	static std::string SerializeMat4(const glm::mat4 mat)
	{
		const float* arr = glm::value_ptr(mat);

		std::vector<float> vector(arr, arr + 16);
		return nlohmann::json(vector).dump();
	}

	static glm::vec3 DeserializeVec3(const std::string s)
	{
		nlohmann::json j = nlohmann::json::parse(s);
		std::vector<float> vector = j;

		return glm::vec3(vector[0], vector[1], vector[2]);
	}

	static glm::mat4 DeserializeMat4(const std::string s)
	{
		nlohmann::json j = nlohmann::json::parse(s);
		std::vector<float> vector = j;

		return glm::mat4(vector[0], vector[1], vector[2], vector[3],
						 vector[4], vector[5], vector[6], vector[7], 
						 vector[8], vector[9], vector[10], vector[11], 
						 vector[12], vector[13], vector[14], vector[15]);
	}
};