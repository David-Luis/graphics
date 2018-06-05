#pragma once

#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Utils
{
	static glm::vec3 GetTranslation(const glm::mat4& transformation)
	{
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(transformation, scale, rotation, translation, skew, perspective);

		return translation;
	}
};