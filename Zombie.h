#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Player;

enum class Type
{
	bloater, // 0
	chaser,  // 1
	crawler,  // 2
	count
};

class Zombie : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string texId = "graphics/bloater.png";
	std::string bloodTexId = "graphics/blood.png";

	Player* target = nullptr;

	sf::Vector2f direction = { 0.0f, 0.0f };
	
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBg;
	sf::Vector2f hpBarOffset = { 0.f, 5.f };

	bool isActive = false;
	bool isAlive = true;

	float per = 0.f; // 변수 명 변경하기..

	int health = 0;
	int maxHealth = 0;
	float speed = 0.0f;
	int damage = 0;

	float attackInterval = 1.f;
	float attackTimer = 0.f;
	float fadeTimer = 0.f;

	sf::Vector2f targetPos = { 100.f, 100.f }; // 플레이어로 변경하기
	
	HitBox hitBox;
	// 생성될 때 랜덤 종류 적용


public:
	Zombie(const std::string& name = "");
	virtual ~Zombie() = default;

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
	
	void OnDamage(int damage);

	sf::FloatRect GetLocalBounds() const override
	{
		return sprite.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return sprite.getGlobalBounds();
	}

	void Attack(float dt);
	void SetRandomType();
	void Movement(float dt);
	void UpdateHpBar();
	void Die();

	const HitBox& GetHitBox() const
	{
		return hitBox;
	}
};