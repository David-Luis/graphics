#pragma once

class Shader;
class Camera;

class ILight
{
public:
	virtual void Use(Shader& shader) = 0;
	virtual void DebugDraw(Camera& camera) = 0;
};

