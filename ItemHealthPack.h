#pragma once
#include "Item.h"
#include "HitBox.h"

class ItemHealthPack : public Item
{
protected:
	sf::Sprite healthPackSprite;
	HitBox hitBox;

public:
	ItemHealthPack(const std::string& name = "healthPack");
	~ItemHealthPack() override = default;

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