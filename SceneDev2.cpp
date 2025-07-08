#include "stdafx.h"
#include "SceneDev2.h"
#include "Zombie.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	Zombie* zombie = (Zombie*)AddGameObject(new Zombie());

	Scene::Init();
}

void SceneDev2::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);
}


void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(uiView);
	//window.draw(cursor);
}