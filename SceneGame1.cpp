#include "stdafx.h"
#include "SceneGame1.h"
#include "Zombie.h"
#include "Item.h"
#include "ItemHealthPack.h"
#include "ItemAmmo.h"
#include "Player.h"
#include "TileMap.h"
#include "DataStruct.h"


SceneGame1::SceneGame1():Scene(SceneIds::Game1)
{
}

void SceneGame1::Init()
{

	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/health_pickup.png");
	texIds.push_back("graphics/ammo_pickup.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/blood.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	TileMap* tileMap = (TileMap*)AddGameObject(new TileMap("TileMap"));
	player = (Player*)AddGameObject(new Player("Player"));
	// �ʱ� ���� ����
	for (int i = 0; i < 100; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

	Scene::Init();

	tileMap->SetMapSize(10, 10);
}

void SceneGame1::Enter()
{
	//std::cout << " SceneDev2::Enter() 호출됨" << std::endl;

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	SpawnZombies(5);

	Scene::Enter();
}

void SceneGame1::Exit()
{
	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	Scene::Exit();
}

void SceneGame1::Update(float dt)
{
	Scene::Update(dt);

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}

	auto it = zombieList.begin();
	while (it != zombieList.end())
	{
		if (!(*it)->GetAlive())
		{
			zombiePool.push_back(*it);
			it = zombieList.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (zombieList.empty())
	{
		SCENE_MGR.ChangeScene(SceneIds::Mode);
		return;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnItems(3);
	}
}

void SceneGame1::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);

	Scene::Draw(window);

	window.setView(uiView);

	//window.draw(cursor);
}

void SceneGame1::SpawnZombies(int count)
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
		zombie->Reset();
		float x = Utils::RandomRange(-150.f, 150.f);
		float y = Utils::RandomRange(-150.f, 150.f);
		zombie->SetPosition(sf::Vector2f(x, y));
		zombieList.push_back(zombie);
	}
}

void SceneGame1::SpawnItems(int counts)
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

TileMap* SceneGame1::GetTileMap()
{
	return (TileMap*)FindGameObject("TileMap");
}