#pragma once
#include "GameObject.h"
class Player : public GameObject
{
protected:
	sf::Sprite player;
	std::string texId = "graphics/player.png";

	sf::Vector2f direction;
	float speed = 0;




public:
	Player(const std::string& name = "");
	virtual ~Player() = default;

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



};

