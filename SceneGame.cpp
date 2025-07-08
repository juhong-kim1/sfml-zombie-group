#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game1)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/player.png");

	player = (Player*)AddGameObject(new Player("Player"));

	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

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
