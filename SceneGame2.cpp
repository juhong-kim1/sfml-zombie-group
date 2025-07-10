#include "stdafx.h"
#include "SceneGame2.h"
#include "Zombie.h"
#include "Item.h"
#include "ItemHealthPack.h"
#include "ItemAmmo.h"
#include "Player.h"
#include "TileMap.h"
#include "TitleScene.h"
#include "GameData.h"

#include "DataStruct.h"


SceneGame2::SceneGame2() :Scene(SceneIds::Game2)
{
}

void SceneGame2::Init()
{


	fontIds.push_back("fonts/DS-DIGIT.ttf");
	fontIds.push_back("fonts/zombiecontrol.ttf");

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


	TileMap* tileMap = (TileMap*)AddGameObject(new TileMap("TileMap"));
	player = (Player*)AddGameObject(new Player("Player"));
	// �ʱ� ���� ����
	for (int i = 0; i < 30; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

	Scene::Init();

	tileMap->SetMapSize(10, 10);
}

void SceneGame2::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	Scene::Enter();
	std::cout << " SceneDev2::Enter() 호출됨" << std::endl;

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	const sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");

	scoreText.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setPosition(100.f, 30.f);

	hiScoreText.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
	hiScoreText.setCharacterSize(50);
	hiScoreText.setFillColor(sf::Color::White);
	hiScoreText.setStyle(sf::Text::Bold);
	hiScoreText.setPosition(1350.f, 30.f);

	ammoText.setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf")); // 폰트는 원하는 걸로
	ammoText.setCharacterSize(50);
	ammoText.setFillColor(sf::Color::White);
	ammoText.setStyle(sf::Text::Bold);
	ammoText.setPosition(100.f, 950.f); // 적당한 위치

	waveText.setFont(font);
	waveText.setCharacterSize(50);
	waveText.setFillColor(sf::Color::White);
	waveText.setStyle(sf::Text::Bold);
	waveText.setPosition(1200.f, 950.f);

	// 좀비 수 텍스트
	zombieCountText.setFont(font);
	zombieCountText.setCharacterSize(50);
	zombieCountText.setFillColor(sf::Color::White);
	zombieCountText.setStyle(sf::Text::Bold);
	zombieCountText.setPosition(1500.f, 950.f);

	pauseText.setFont(font);
	pauseText.setString("PRESS ENTER\nTO CONTINUE");
	pauseText.setCharacterSize(50);
	pauseText.setPosition(100.f, 100.f);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setStyle(sf::Text::Bold);

	pauseText.setOrigin(pauseText.getLocalBounds().width / 2.f, pauseText.getLocalBounds().height / 2.f);
	pauseText.setPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);


	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	SpawnZombies(5);

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

	for (Zombie* zombie : zombiePool)
	{
		zombie->SetActive(false);
	}

	Scene::Exit();
}

void SceneGame2::Update(float dt)
{

	if (player != nullptr)
	{
		ammoText.setString(
			"Ammo: " + std::to_string(player->GetAmmoInClip()) +
			" / " + std::to_string(player->GetReserveAmmo()));
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

	// 2. 좀비 다 죽으면 다음 씬
	if (zombieList.empty())
	{
		SCENE_MGR.ChangeScene(SceneIds::Mode);
		return;
	}
	// 텍스트 내용 업데이트
	waveText.setString("Wave: " + std::to_string(wave));
	zombieCountText.setString("Zombies: " + std::to_string(zombieList.size()));


	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		isPaused = !isPaused;

	}
	if (isPaused)
	{

		return;
	}
	Scene::Update(dt);

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}



}

void SceneGame2::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	Scene::Draw(window);
	window.setView(uiView);
	window.draw(ammoText);
	window.draw(waveText);
	window.draw(zombieCountText);
	window.draw(scoreText);
	window.draw(hiScoreText);
	window.draw(cursor);


	if (isPaused)
	{
		window.setView(uiView);
		window.draw(pauseText);

	}
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
			zombie->Reset();
		}
		zombie->SetParentScene(this);

		zombie->SetRandomType();
		zombie->Reset();
		float x = Utils::RandomRange(-150.f, 150.f);
		float y = Utils::RandomRange(-150.f, 150.f);
		zombie->SetPosition(sf::Vector2f(x, y));
		zombieList.push_back(zombie);
	}
}

void SceneGame2::SpawnItems(int counts)
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

TileMap* SceneGame2::GetTileMap()
{
	return (TileMap*)FindGameObject("TileMap");
}

void SceneGame2::AddScore(int amount)
{
	currentScore += amount;
	GameData::currentScore = currentScore;//공유저장소 기록

	// 하이스코어 갱신
	if (currentScore > GameData::hiScore)
	{
		GameData::hiScore = currentScore;
		hiScoreText.setString("HI SCORE: " + std::to_string(GameData::hiScore));
	}

	scoreText.setString("SCORE: " + std::to_string(currentScore));
}

void SceneGame2::SpawnHealthPack()
{
	if (healthPackExists) return; // 이미 존재하면 생성하지 않음

	ItemHealthPack* healthPack = new ItemHealthPack();
	AddGameObject(healthPack);
	healthPack->Init();
	healthPack->Reset();
	healthPack->lifeTimer = 0.0f; // 생존 시간 초기화

	// 벽 안쪽에서 랜덤 위치에 생성
	float x = Utils::RandomRange(-150.f, 150.f);
	float y = Utils::RandomRange(-150.f, 150.f);
	healthPack->SetPosition(sf::Vector2f(x, y));

	itemList.push_back(healthPack);
	healthPackExists = true;
}

void SceneGame2::SpawnAmmo()
{
	if (ammoExists) return; // 이미 존재하면 생성하지 않음

	ItemAmmo* ammo = new ItemAmmo();
	AddGameObject(ammo);
	ammo->Init();
	ammo->Reset();
	ammo->lifeTimer = 0.0f; // 생존 시간 초기화

	// 벽 안쪽에서 랜덤 위치에 생성
	float x = Utils::RandomRange(-150.f, 150.f);
	float y = Utils::RandomRange(-150.f, 150.f);
	ammo->SetPosition(sf::Vector2f(x, y));

	itemList.push_back(ammo);
	ammoExists = true;
}
