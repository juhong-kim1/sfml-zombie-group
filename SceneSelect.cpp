#include "stdafx.h"
#include "SceneSelect.h"
#include "DataStruct.h"

SceneSelect::SceneSelect()
	:Scene(SceneIds::Select)
{
}

void SceneSelect::Init()
{
	Scene::Init();
}

void SceneSelect::Enter()
{
	Scene::Enter();
}

void SceneSelect::Exit()
{
	Scene::Exit();
}

void SceneSelect::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		std::cout << "Increased rate of Fire" << std::endl;
		DataStruct::IncreaseRateOfFire(0.1f);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		std::cout << "increased clip sizecenxt reload" << std::endl;
		DataStruct::IncreaseClipSize(6);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		std::cout << "increased max health" << std::endl;
		DataStruct::IncreaseMaxHealth(10);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	{
		std::cout << "increased run speed" << std::endl;
		DataStruct::IncreaseRunSpeed(10);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
	{
		std::cout << "more and better health pickups" << std::endl;
		DataStruct::IncreaseHealAmount(10);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num6))
	{
		std::cout << "more and better ammo pickups" << std::endl;
		DataStruct::IncreaseAmmoAmount(6);
	}

	Scene::Update(dt);
}

void SceneSelect::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}