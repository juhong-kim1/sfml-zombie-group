#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	player.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	player.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	player.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	player.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(player, preset);
	}
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Player::Release()
{
}

void Player::Reset()
{
	player.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::TL);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);


}

void Player::Update(float dt)
{
	SetOrigin(Origins::TL);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(player);
}