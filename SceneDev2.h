#pragma once
#include "Scene.h"

class Player;
class Zombie;
class Item;
class TileMap;

class SceneDev2 : public Scene
{
protected:
	std::list<Zombie*> zombieList; // Ȱ��ȭ�� ����
	std::list<Zombie*> zombiePool; // ��Ȱ��ȭ�� ����
	std::list<Item*> itemList;	   // ������ ����Ʈ

	Player* player = nullptr;
	bool isPaused = false;
	sf::Text pauseText;
	sf::Text waveText;
	sf::Text zombieCountText;
	int wave = 1;
	int zombie = 1;

public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SpawnZombies(int count);
	void SpawnItems(int counts);
	void setTextZombie(int count);
	std::list<Zombie*> GetZombies()
	{
		return zombieList;
	}
	TileMap* GetTileMap();

};

