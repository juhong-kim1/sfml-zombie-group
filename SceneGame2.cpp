#include "stdafx.h"
#include "SceneGame2.h"
#include "Zombie.h"
#include "Item.h"
#include "ItemHealthPack.h"
#include "ItemAmmo.h"
#include "Player.h"
#include "TileMap.h"


SceneGame2::SceneGame2() :Scene(SceneIds::Game2)
{
}

void SceneGame2::Init()
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
	texIds.push_back("graphics/crosshair.png");

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

	tileMap->SetMapSize(20, 20);
}

void SceneGame2::Enter()
{
	//std::cout << " SceneDev2::Enter() 호출됨" << std::endl;

	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	SpawnZombies(10);

	SpawnHealthPack();
	SpawnAmmo();

	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
}

void SceneGame2::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	for (Item* item : itemList)
	{
		item->SetActive(false);
	}
	itemList.clear();

	healthPackRespawnTimer = 0.0f;
	ammoRespawnTimer = 0.0f;
	healthPackExists = false;
	ammoExists = false;

	Scene::Exit();
}

void SceneGame2::Update(float dt)
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

	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	auto itemIt = itemList.begin();
	while (itemIt != itemList.end())
	{
		if (!(*itemIt)->GetActive())
		{
			if (dynamic_cast<ItemHealthPack*>(*itemIt))
			{
				healthPackExists = false;
				healthPackRespawnTimer = 0.0f;
			}
			else if (dynamic_cast<ItemAmmo*>(*itemIt))
			{
				ammoExists = false;
				ammoRespawnTimer = 0.0f;
			}

			itemIt = itemList.erase(itemIt);
		}
		else
		{
			(*itemIt)->lifeTimer += dt;
			if ((*itemIt)->lifeTimer >= 5.0f)
			{
				if (dynamic_cast<ItemHealthPack*>(*itemIt))
				{
					healthPackExists = false;
					healthPackRespawnTimer = 0.0f;
				}
				else if (dynamic_cast<ItemAmmo*>(*itemIt))
				{
					ammoExists = false;
					ammoRespawnTimer = 0.0f;
				}

				(*itemIt)->SetActive(false);
				itemIt = itemList.erase(itemIt);
			}
			else
			{
				++itemIt;
			}
		}
	}

	if (!healthPackExists)
	{
		healthPackRespawnTimer += dt;
		if (healthPackRespawnTimer >= 5.0f)
		{
			SpawnHealthPack();
		}
	}

	if (!ammoExists)
	{
		ammoRespawnTimer += dt;
		if (ammoRespawnTimer >= 5.0f)
		{
			SpawnAmmo();
		}
	}

	if (zombieList.empty())
	{
		SCENE_MGR.ChangeScene(SceneIds::Game3);
		return;
	}

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SpawnItems(3);
	//}
}

void SceneGame2::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(cursor);

	//window.draw(cursor);
}

void SceneGame2::SpawnZombies(int count)
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
		zombie->SetRandomType();
		zombie->Reset();
		float x = Utils::RandomRange(-400.f, 400.f);
		float y = Utils::RandomRange(-400.f, 400.f);
		zombie->SetPosition(sf::Vector2f(x, y));
		zombieList.push_back(zombie);
	}
}

//void SceneGame2::SpawnItems(int counts)
//{
//	for (int i = 0; i < counts; i++)
//	{
//		Item* item = nullptr;
//
//		int random = Utils::RandomRange(0, (int)Item::ItemType::count);
//
//		if (random == (int)Item::ItemType::HealthPack)
//		{
//			item = new ItemHealthPack();
//		}
//		else if (random == (int)Item::ItemType::Ammo)
//		{
//			item = new ItemAmmo();
//		}
//
//		if (item != nullptr)
//		{
//			AddGameObject(item);
//			item->Init();
//			item->Reset();
//			item->SetPosition(Utils::RandomInUnitCircle() * 300.f);
//			itemList.push_back(item);
//		}
//	}
//}

TileMap* SceneGame2::GetTileMap()
{
	return (TileMap*)FindGameObject("TileMap");
}

void SceneGame2::SpawnHealthPack()
{
	if (healthPackExists) return;

	ItemHealthPack* healthPack = new ItemHealthPack();
	AddGameObject(healthPack);
	healthPack->Init();
	healthPack->Reset();
	healthPack->lifeTimer = 0.0f;

	// 벽 안쪽에서 랜덤 위치에 생성
	float x = Utils::RandomRange(-400.f, 400.f);
	float y = Utils::RandomRange(-400.f, 400.f);
	healthPack->SetPosition(sf::Vector2f(x, y));

	itemList.push_back(healthPack);
	healthPackExists = true;
}

void SceneGame2::SpawnAmmo()
{
	if (ammoExists) return;

	ItemAmmo* ammo = new ItemAmmo();
	AddGameObject(ammo);
	ammo->Init();
	ammo->Reset();
	ammo->lifeTimer = 0.0f;

	float x = Utils::RandomRange(-400.f, 400.f);
	float y = Utils::RandomRange(-400.f, 400.f);
	ammo->SetPosition(sf::Vector2f(x, y));

	itemList.push_back(ammo);
	ammoExists = true;
}