#pragma once
#include "Scene.h"

class Zombie;

class SceneDev2 : public Scene
{
protected:
	std::list<Zombie*> zombieList; // 활성화된 좀비
	std::list<Zombie*> zombiePool; // 비활성화된 좀비

public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SpawnZombies(int count);
};

