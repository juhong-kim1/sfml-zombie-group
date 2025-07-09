#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "HitBox.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

bool Player::CheckBorder(const sf::Vector2f pos)
{
	sf::FloatRect localBounds = player.getLocalBounds();
	sf::Transformable temp;
	temp.setPosition(pos);
	hitBox.UpdateTransform(temp, localBounds);

	sf::FloatRect wallet(300, 300, 100, 100);
	return hitBox.rect.getGlobalBounds().intersects(wallet);
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
	sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();

	player.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);

	direction = { 0.f, 0.f };
	look = { 1.f, 1.f };

}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2f nextPos = position + direction * speed * dt;

	if (!CheckBorder(nextPos))
	{
		SetPosition(nextPos);
	}


	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));

	hitBox.UpdateTransform(player, player.getLocalBounds());

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(player);
	hitBox.Draw(window);
}

void Player::Effect1()
{

}

void Player::Effect2()
{
}

void Player::Effect3()
{
}

void Player::Effect4()
{
}

void Player::Effect5()
{
}

void Player::Effect6()
{
}
