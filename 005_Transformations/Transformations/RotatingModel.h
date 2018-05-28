#pragma once

#include <Engine/Model.h>

#include <vector>

class RotatingModel : public Model
{
public:
	RotatingModel(Shader* shader, Texture* texture, Mesh* mesh, float speed);
	~RotatingModel() override {}
	RotatingModel(const RotatingModel&) = delete;
	RotatingModel& operator=(RotatingModel const&) = delete;

private:
	void Update() override;	

	float m_speed;
};
