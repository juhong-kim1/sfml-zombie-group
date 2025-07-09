#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneGame;
class HitBox;

class Player : public GameObject
{
protected:
	sf::Sprite player;
	std::string texId = "graphics/player.png";

	sf::Vector2f look;
	sf::Vector2f direction;
	float speed = 500.f;

	SceneGame* sceneGame = nullptr;
	HitBox hitBox;
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
	
	void Effect1();
	void Effect2();
	void Effect3();
	void Effect4();
	void Effect5();
	void Effect6();



};

