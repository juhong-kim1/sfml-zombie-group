#pragma once
#include "Scene.h"

class Zombie;
class Item;
class Player;
class TileMap;

class SceneGame1 : public Scene
{
protected:
	std::list<Zombie*> zombieList; // Ȱ��ȭ�� ����
	std::list<Zombie*> zombiePool; // ��Ȱ��ȭ�� ����
	std::list<Item*> itemList;	   // ������ ����Ʈ

	Player* player = nullptr;
	TileMap* tileMap = nullptr;

	float healthPackRespawnTimer = 0.0f;
	float ammoRespawnTimer = 0.0f;
	bool healthPackExists = false;
	bool ammoExists = false;
	
	bool isPaused = false;
	sf::Text pauseText;
	sf::Text waveText;
	sf::Text zombieCountText;
	sf::Text ammoText;
	sf::Text scoreText;
	sf::Text hiScoreText;
	int wave = 1;
	int currentScore = 0;
	int zombie = 1;

	sf::Sprite cursor;

public:
	SceneGame1();
	~SceneGame1() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SpawnZombies(int count);
	void SpawnItems(int counts);
	std::list<Zombie*> GetZombies()
	{
		return zombieList;
	}

	TileMap* GetTileMap();
	void AddScore(int amount);

	void SpawnHealthPack();
	void SpawnAmmo();
};
