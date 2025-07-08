#include "stdafx.h"
#include "Zombie.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Zombie::Init()
{
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	SetRandomType(); // 랜덤 타입 설정

	SetOrigin(Origins::MC);
	SetPosition({ 0.0f, 0.0f });
	SetRotation(0.0f);
	SetScale({ 1.0f, 1.0f });

	hpBarBg.setFillColor(sf::Color::White);
	hpBar.setFillColor(sf::Color::Red);

	hpBarBg.setSize({ 30.f, 5.f });
	hpBar.setSize({ 30.f, 5.f });

	Utils::SetOrigin(hpBarBg, Origins::ML);
	Utils::SetOrigin(hpBar, Origins::ML);

	per = hpBar.getSize().x / health;
}

void Zombie::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		OnDamage(10);
	}

	UpdateHpBar(); // 좀비 체력바 업데이트
	Movement(dt);  // 좀비 이동

	if (health <= 0)
	{
		Die();
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	// 최초 데미지를 입은 후 체력바가 나타나도록 함
	if (health != maxHealth)
	{
		window.draw(hpBarBg);
		window.draw(hpBar);
	}
}

// 좀비 피격
void Zombie::OnDamage(int damage)
{
	if (health <= 0)
	{
		health = 0;
		return;
	}

	health -= damage;
}

// 좀비 타입 설정
void Zombie::SetRandomType()
{
	int random = Utils::RandomRange(0, (int)Type::count);

	if (random == (int)Type::bloater)
	{
		texId = "graphics/bloater.png";
		maxHealth = 200;
		speed = 50.f;
		damage = 50;
	}
	else if (random == (int)Type::chaser)
	{
		texId = "graphics/chaser.png";
		maxHealth = 100;
		speed = 150.f;
		damage = 50;
	}
	else if (random == (int)Type::crawler)
	{
		texId = "graphics/crawler.png";
		maxHealth = 100;
		speed = 30.0f;
		damage = 50;
	}
	
	sprite.setTexture(TEXTURE_MGR.Get(texId), true);

	health = maxHealth;
}

// 좀비 이동
void Zombie::Movement(float dt)
{
	// 이동
	if (Utils::Distance(targetPos, position) > 0.5f)
	{
		SetPosition(position + direction * speed * dt);
	}
	
	// 이동하고자 하는 방향을 바라보게 회전
	direction = Utils::GetNormal(targetPos - position);
	SetRotation(Utils::Angle(direction));
}

// HP Bar 업데이트
void Zombie::UpdateHpBar()
{
	hpBarBg.setPosition(hpBar.getPosition());
	hpBar.setPosition((position.x - GetLocalBounds().width * 0.5f) + hpBarOffset.x, GetGlobalBounds().top - hpBarOffset.y);

	float fill = per * health;
	hpBar.setSize({ fill, 5 });
}

// 사망 처리
void Zombie::Die()
{
	SetActive(false);
}