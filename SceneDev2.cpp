#include "stdafx.h"
#include "SceneDev2.h"
#include "Zombie.h"
#include "Item.h"
#include "ItemHealthPack.h"
#include "ItemAmmo.h"
#include "Player.h"
#include "TileMap.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
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
	texIds.push_back("graphics/blood.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");
	fontIds.push_back("fonts/zombiecontrol.ttf");

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
	Scene::Enter();

	const sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();


	waveText.setFont(font);
	waveText.setCharacterSize(40);
	waveText.setFillColor(sf::Color::White);
	waveText.setStyle(sf::Text::Bold);
	waveText.setPosition(1400.f, 950.f);

	// 좀비 수 텍스트
	zombieCountText.setFont(font);
	zombieCountText.setCharacterSize(40);
	zombieCountText.setFillColor(sf::Color::White);
	zombieCountText.setStyle(sf::Text::Bold);
	zombieCountText.setPosition(1400.f, 1000.f);

	pauseText.setFont(font);
	pauseText.setString("PRESS ENTER\nTO CONTINUE");
	pauseText.setCharacterSize(180);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setStyle(sf::Text::Bold);


	pauseText.setOrigin(pauseText.getLocalBounds().width / 2.f, pauseText.getLocalBounds().height / 2.f);
	pauseText.setPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);

	worldView.setSize(windowSize);
	worldView.setCenter( windowSize * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	SpawnZombies(10);

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
		SpawnItems(3);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);//wave 표시
	Scene::Draw(window);

	window.setView(uiView);//ui 뷰로 전환
	window.draw(zombieCountText);//좀비 수 표시
	window.draw(waveText);


	if (isPaused)
	{
		window.setView(uiView);
		window.draw(pauseText);
	}

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
		zombie->SetRandomType();
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


void SceneDev2::setTextZombie(int count)
{
}

TileMap* SceneDev2::GetTileMap()
{
	return (TileMap*)FindGameObject("TileMap");
}
