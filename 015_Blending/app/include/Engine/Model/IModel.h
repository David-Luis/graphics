#pragma once

#include <vector>

class CCamera;
class CLightsSet;

class IModel
{
public:

	virtual void Update() = 0;
	virtual void Draw(CCamera& camera, CLightsSet& lights) = 0;
};

