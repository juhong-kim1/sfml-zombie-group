#include "stdafx.h"
#include "ItemAmmo.h"


ItemAmmo::ItemAmmo(const std::string& name)
	:Item(name)
{
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
	ammoSprite.setTexture(TEXTURE_MGR.Get(texId));
}

void ItemAmmo::Update(float dt)
{
	//if (Utils::CheckCollision(hitBox.rect, player->GetHitBox().rect))
	//{
	//	Use();
	//}
}

void ItemAmmo::Draw(sf::RenderWindow& window)
{
	window.draw(ammoSprite);
}

void ItemAmmo::Use()
{
	// �÷��̾� �Ѿ� ����
	std::cout << "źâ ����" << std::endl;

	// ��� �� ��Ȱ��ȭ
	SetActive(false);
}
