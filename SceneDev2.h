#pragma once
#include "Scene.h"

class Zombie;
class Item;

class SceneDev2 : public Scene
{
protected:
	std::list<Zombie*> zombieList; // 활성화된 좀비
	std::list<Zombie*> zombiePool; // 비활성화된 좀비
	std::list<Item*> itemList;	   // 아이템 리스트

public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SpawnZombies(int count);
	void SpawnItems(int counts);
};

