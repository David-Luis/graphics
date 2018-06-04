#pragma once

#include <vector>

class Shader;
class Camera;
class Light;
class ILight;

class IModel
{
public:

	virtual void Update() = 0;
	virtual void Draw(Shader& shader, Camera& camera, std::vector<ILight*> lights) = 0;
};

