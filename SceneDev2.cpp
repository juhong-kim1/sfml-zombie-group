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

	// 초기 좀비 생성
	for (int i = 0; i < 100; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

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

void SceneDev2::Exit()
{
	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	auto it = zombieList.begin();
	while (it != zombieList.end())
	{
		if (!(*it)->GetActive())
		{
			zombiePool.push_back(*it);
			it = zombieList.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(10);
	}
}


void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(uiView);

	//window.draw(cursor);
}

void SceneDev2::SpawnZombies(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Zombie* zombie = nullptr;
		if (zombiePool.empty())
		{
			zombie = (Zombie*)AddGameObject(new Zombie());
			zombie->Init();
		}
		else
		{
			zombie = zombiePool.front();
			zombiePool.pop_front();
			zombie->SetActive(true);
		}
		//zombie->SetRandomType();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);
		zombieList.push_back(zombie);
	}
}