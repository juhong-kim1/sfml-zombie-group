#include "stdafx.h"
#include "SceneGame.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game1)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/player.png");

	Scene::Init();
}

void SceneGame::Enter()
{
	Scene::Enter();
}
void SceneGame::Exit()
{
	Scene::Exit();

}
void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
}
