#include "stdafx.h"
#include "ItemHealthPack.h"
#include "Player.h"


ItemHealthPack::ItemHealthPack(const std::string& name)
	:Item(name)
{
}

void ItemHealthPack::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	healthPackSprite.setPosition(pos);
}

void ItemHealthPack::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	healthPackSprite.setRotation(rot);
}

void ItemHealthPack::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	healthPackSprite.setScale(s);
}

void ItemHealthPack::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	healthPackSprite.setOrigin(o);
}

void ItemHealthPack::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(healthPackSprite, preset);
	}
}


void ItemHealthPack::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;

	texId = "graphics/health_pickup.png";
}

void ItemHealthPack::Release()
{
}

void ItemHealthPack::Reset()
{
	target = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	healthPackSprite.setTexture(TEXTURE_MGR.Get(texId));
}

void ItemHealthPack::Update(float dt)
{
	if (Utils::CheckCollision(hitBox.rect, target->GetHitBox().rect))
	{
		Use();
	}

	hitBox.UpdateTransform(healthPackSprite, healthPackSprite.getLocalBounds());
}

void ItemHealthPack::Draw(sf::RenderWindow& window)
{
	window.draw(healthPackSprite);
	hitBox.Draw(window);
}

void ItemHealthPack::Use()
{
	// 체력 회복
	 //playerHp += 10;
	std::cout << "체력 회복" << std::endl;

	// 사용 후 비활성화
	SetActive(false);
}