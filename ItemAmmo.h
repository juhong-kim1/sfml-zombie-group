#pragma once
#include "Item.h"
#include "HitBox.h"

class ItemAmmo : public Item
{
	sf::Sprite ammoSprite;
	HitBox hitBox;

public:
	ItemAmmo(const std::string& name = "ammo");
	~ItemAmmo() override = default;

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
	void Use() override;

	const HitBox& GetHitBox() const
	{
		return hitBox;
	}
};