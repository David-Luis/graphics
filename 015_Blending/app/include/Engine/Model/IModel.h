#pragma once

#include <vector>

class CShader;
class CCamera;
class CLightsSet;

class IModel
{
public:

	virtual void Update() = 0;
	virtual void Draw(CShader& shader, CCamera& camera, CLightsSet& lights) = 0;
};

