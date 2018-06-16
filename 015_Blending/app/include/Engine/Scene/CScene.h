#pragma once

#include <vector>
#include <algorithm>

class CCamera;
class CLightsSet;
class IModel;

class CScene
{
public:
	CScene();

	virtual ~CScene();
	CScene(const CScene&) = delete;
	CScene& operator=(CScene const&) = delete;

	virtual void Update(float dt) {}
	virtual void Draw();

	void SetCamera(CCamera* camera) { m_camera = camera; }
	CCamera* GetCamera() { return m_camera; }

	void SetLightsSet(CLightsSet* lightsSet) { m_lightsSet = lightsSet; }
	CLightsSet* GetLightsSet() { return m_lightsSet; }

	void SetModels(const std::vector<IModel*>& models) { m_models = models; }
	void AddModel(IModel* model) { m_models.push_back(model); }
	void RemoveModel(IModel* model) { m_models.erase(std::remove(m_models.begin(), m_models.end(), model), m_models.end()); }

private:
	CCamera* m_camera;
	CLightsSet* m_lightsSet;
	std::vector<IModel*> m_models;
};

