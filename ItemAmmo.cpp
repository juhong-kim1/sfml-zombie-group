#include "stdafx.h"
#include "ItemAmmo.h"
#include "Player.h"

ItemAmmo::ItemAmmo(const std::string& name)
	:Item(name)
{
}

void ItemAmmo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	ammoSprite.setPosition(pos);
}

void ItemAmmo::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	ammoSprite.setRotation(rot);
}

void ItemAmmo::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	ammoSprite.setScale(s);
}

void ItemAmmo::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	ammoSprite.setOrigin(o);
}

void ItemAmmo::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(ammoSprite, preset);
	}
}

void ItemAmmo::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;

	texId = "graphics/ammo_pickup.png";
}

void ItemAmmo::Release()
{
}

void ItemAmmo::Reset()
{
	target = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	ammoSprite.setTexture(TEXTURE_MGR.Get(texId));
}

void ItemAmmo::Update(float dt)
{
	if (Utils::CheckCollision(hitBox.rect, target->GetHitBox().rect))
	{
		Use();
	}

	hitBox.UpdateTransform(ammoSprite, ammoSprite.getLocalBounds());
}

void ItemAmmo::Draw(sf::RenderWindow& window)
{
	window.draw(ammoSprite);
	hitBox.Draw(window);
}

void ItemAmmo::Use()
{
	// 플레이어 총알 충전
	std::cout << "탄창 충전" << std::endl;

	// 사용 후 비활성화
	SetActive(false);
}