#pragma once

#include <vector>

class Shader;
class Camera;
class Light;
class PointLight;

class IModel
{
public:

	virtual void Update() = 0;
	virtual void Draw(Shader& shader, Camera& camera, std::vector<PointLight*> lights) = 0;
};

