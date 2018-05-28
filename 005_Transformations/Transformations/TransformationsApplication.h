#pragma once

#include <Engine/OpenGLApplication.h>

#include <vector>

class Model;

class TransformationsApplication : public OpenGLApplication
{
public:
	TransformationsApplication();
	~TransformationsApplication() override {}
	TransformationsApplication(const TransformationsApplication&) = delete;
	TransformationsApplication& operator=(TransformationsApplication const&) = delete;

private:
	void OnInit() override;
	void OnDraw() override;

	void LoadModels();
	Model* LoadModel1();
	Model* LoadModel2();
	void DrawModels();

	std::vector<Model*> m_models;
};
