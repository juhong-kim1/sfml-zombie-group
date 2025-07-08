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
	// ü�� ȸ��
	// playerHp += 10;
	std::cout << "ü�� ȸ��" << std::endl;

	// ��� �� ��Ȱ��ȭ
	SetActive(false);
}
