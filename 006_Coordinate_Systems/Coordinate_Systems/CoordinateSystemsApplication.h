#pragma once

#include <Engine/OpenGLApplication.h>

#include <vector>

class Model;

class CoordinateSystemsApplication : public OpenGLApplication
{
public:
	CoordinateSystemsApplication();
	~CoordinateSystemsApplication() override {}
	CoordinateSystemsApplication(const CoordinateSystemsApplication&) = delete;
	CoordinateSystemsApplication& operator=(CoordinateSystemsApplication const&) = delete;

private:
	void OnInit() override;
	void OnDraw() override;

	void LoadModels();
	Model* LoadModel1();
	Model* LoadModel2();
	void DrawModels();

	std::vector<Model*> m_models;
};
