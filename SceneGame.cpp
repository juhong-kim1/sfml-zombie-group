#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Title)
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

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape wall(sf::Vector2f(100.f, 100.f));
	wall.setPosition(300.f, 300.f);
	wall.setFillColor(sf::Color::Red);
	window.draw(wall);

	window.setView(worldView);
	Scene::Draw(window);
}
