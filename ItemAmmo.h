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