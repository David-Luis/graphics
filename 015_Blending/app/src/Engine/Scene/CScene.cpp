#include <Engine/Scene/CScene.h>

#include <Engine/Model/CModel.h>
#include <Engine/Light/CLightsSet.h>
#include <Engine/Camera/CCamera.h>

#include <assert.h>

CScene::CScene()
{

}

CScene::~CScene()
{

}

void CScene::Draw()
{
	assert(m_camera);
	assert(m_lightsSet);

	for (const auto& model : m_models)
	{
		model->Update();
		model->Draw(*m_camera, *m_lightsSet);
	}

	m_lightsSet->DebugDraw(*m_camera);
}