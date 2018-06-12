#pragma once

#include <vector>

class Shader;
class Camera;
class LightsSet;

class IModel
{
public:

	virtual void Update() = 0;
	virtual void Draw(Shader& shader, Camera& camera, LightsSet& lights) = 0;
};

