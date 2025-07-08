#include "stdafx.h"
#include "ItemHealthPack.h"


ItemHealthPack::ItemHealthPack(const std::string& name)
	:Item(name)
{
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
	healthPackSprite.setTexture(TEXTURE_MGR.Get(texId));
}

void ItemHealthPack::Update(float dt)
{
	//if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
	//{
	//	Use();
	//}
}

void ItemHealthPack::Draw(sf::RenderWindow& window)
{
	window.draw(healthPackSprite);
}

void ItemHealthPack::Use()
{
	// 체력 회복
	// playerHp += 10;
	std::cout << "체력 회복" << std::endl;

	// 사용 후 비활성화
	SetActive(false);
}
