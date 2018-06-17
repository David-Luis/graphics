#pragma once

#include <Lib/json.hpp>

#include <vector>
#include <algorithm>

class CCamera;
class CLightsSet;
class CModel;

class CScene
{
public:
	friend std::ostream &operator<<(std::ostream&, const CScene&);
	friend std::istream &operator>>(std::istream &stream, CScene &t);
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

	void SetModels(const std::vector<CModel*>& models) { m_models = models; }
	void AddModel(CModel* model) { m_models.push_back(model); }
	void RemoveModel(CModel* model) { m_models.erase(std::remove(m_models.begin(), m_models.end(), model), m_models.end()); }
	std::vector<CModel*> GetModels() { return m_models; }
	
	virtual nlohmann::json ToJson() const;
	virtual void FromJson(nlohmann::json);

private:
	CCamera* m_camera;
	CLightsSet* m_lightsSet;
	std::vector<CModel*> m_models;
};

