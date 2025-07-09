#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "TitleScene.h"
#include"ModeScene.h"
#include "effect.h"

void SceneMgr::Init()
{

	scenes.push_back(new TitleScene());
	scenes.push_back(new ModeScene());

	scenes.push_back(new effect(SceneIds::Game1));
	scenes.push_back(new effect(SceneIds::Game2));
	scenes.push_back(new effect(SceneIds::Game3));
	scenes.push_back(new effect(SceneIds::Game4));
	scenes.push_back(new effect(SceneIds::Game5));
	scenes.push_back(new effect(SceneIds::Game6));
	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		if (scene->Id == currentScene)
		{
			scene->Exit();
		}
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[(int)currentScene]->Enter();
	}

	scenes[(int)currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}
