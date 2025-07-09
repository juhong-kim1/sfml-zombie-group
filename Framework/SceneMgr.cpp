#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev2.h"
#include "TitleScene.h"
#include"ModeScene.h"
#include"SceneGame1.h"
#include"SceneGame2.h"
#include"SceneGame3.h"
#include"SceneGame4.h"
#include"SceneGame5.h"
#include"SceneGame6.h"
#include"SceneSelect.h"
#include "effect.h"

void SceneMgr::Init()
{

	scenes.push_back(new TitleScene());
	scenes.push_back(new ModeScene());
	scenes.push_back(new SceneGame1());
	scenes.push_back(new SceneGame2());
	scenes.push_back(new SceneGame3());
	scenes.push_back(new SceneGame4());
	scenes.push_back(new SceneGame5());
	scenes.push_back(new SceneDev2());
	scenes.push_back(new SceneSelect());

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
