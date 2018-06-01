#pragma once

class Shader;
class Camera;

class IModel
{
public:

	virtual void Update() = 0;
	virtual void Draw(Shader& shader, Camera& camera) = 0;
};

