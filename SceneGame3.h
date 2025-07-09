#pragma once
#include "Scene.h"

class Zombie;
class Item;
class Player;
class TileMap;

class SceneGame3 : public Scene
{
protected:
	std::list<Zombie*> zombieList; // Ȱ��ȭ�� ����
	std::list<Zombie*> zombiePool; // ��Ȱ��ȭ�� ����
	std::list<Item*> itemList;	   // ������ ����Ʈ

	Player* player = nullptr;

public:
	SceneGame3();
	~SceneGame3() override = default;

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

};