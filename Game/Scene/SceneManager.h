/*
	@file	SceneManager.h
	@brief	�V�[���}�l�[�W���N���X
*/
#pragma once
#include "IScene.h"

// �O���錾
class CommonResources;

class SceneManager
{
private:
	std::unique_ptr<IScene> m_currentScene;
	CommonResources* m_commonResources;


public:
	SceneManager();
	~SceneManager();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();


private:
	void ChangeScene(IScene::SceneID sceneID);
	void CreateScene(IScene::SceneID sceneID);
	void DeleteScene();
};
