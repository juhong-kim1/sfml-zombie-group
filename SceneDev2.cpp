#include "stdafx.h"
#include "SceneDev2.h"
#include "Zombie.h"
#include "Item.h"
#include "ItemHealthPack.h"
#include "ItemAmmo.h"
#include "Player.h"
#include "TileMap.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Game6)
{
}

void SceneDev2::Init()
{
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/health_pickup.png");
	texIds.push_back("graphics/ammo_pickup.png");
	texIds.push_back("graphics/bullet.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	AddGameObject(new TileMap("TileMap"));
	player = (Player*)AddGameObject(new Player("Player"));
	// �ʱ� ���� ����
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

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}

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
		SpawnItems(3);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);

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

void SceneDev2::SpawnItems(int counts)
{
	for (int i = 0; i < counts; i++)
	{
		Item* item = nullptr;

		int random = Utils::RandomRange(0, (int)Item::ItemType::count);

		if (random == (int)Item::ItemType::HealthPack)
		{
			item = new ItemHealthPack();
		}
		else if (random == (int)Item::ItemType::Ammo)
		{
			item = new ItemAmmo();
		}

		if (item != nullptr)
		{
			AddGameObject(item);
			item->Init();
			item->Reset();
			item->SetPosition(Utils::RandomInUnitCircle() * 300.f);
			itemList.push_back(item);
		}
	}
}