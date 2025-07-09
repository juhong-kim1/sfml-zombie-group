#pragma once
#include "Scene.h"

class SceneSelect : public Scene
{
protected:
	//enum class StatOptions
	//{
	//	None,
	//	Fire,
	//	Reload,
	//	MaxHealth,
	//	RunSpeed,
	//	HealthPickUps,
	//	AmmoPickUps,
	//	count
	//};

	//StatOptions seletedOption = StatOptions::None;

public:
	SceneSelect();
	~SceneSelect() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};