#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneDev2;
class HitBox;
class Bullet;

class Player : public GameObject
{
protected:
	sf::Sprite player;
	std::string texId = "graphics/player.png";

	std::list<Bullet*> bulletList;
	std::list<Bullet*> bulletPool;

	sf::Vector2f look;
	sf::Vector2f direction;
	float speed = 500.f;

	SceneDev2* sceneDev2 = nullptr;
	HitBox hitBox;

	int shootInterval = 0.5f;
	int shootTimer = 0.f;
	

public:
	Player(const std::string& name = "");
	virtual ~Player() = default;

	bool CheckBorder(const sf::Vector2f pos);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	const HitBox& GetHitBox() const
	{
		return hitBox;
	}

	void Shoot();
};