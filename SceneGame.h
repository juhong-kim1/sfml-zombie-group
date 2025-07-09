#pragma once
#include "Scene.h"

class Player;
class Zombie;
class Item;
class TileMap;


class SceneGame : public Scene
{
protected:
	std::list<Zombie*> zombieList; // Ȱ��ȭ�� ����
	std::list<Zombie*> zombiePool; // ��Ȱ��ȭ�� ����
	std::list<Item*> itemList;

	Player* player = nullptr;
	bool isPaused = false;
	sf::Text pauseText;
	sf::Text waveText;
	sf::Text zombieCountText;
	int wave = 1;
	int zombie = 1;

public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void setTextZombie(int count);
	std::list<Zombie*> GetZombies()
	{
		return zombieList;
	}
	TileMap* GetTileMap();






};

