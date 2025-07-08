#pragma once
#include "Scene.h"

class Zombie;

class SceneDev2 : public Scene
{
protected:
	std::list<Zombie*> zombieList; // Ȱ��ȭ�� ����
	std::list<Zombie*> zombiePool; // ��Ȱ��ȭ�� ����

public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SpawnZombies(int count);
};

