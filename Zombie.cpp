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
	SetRandomType(); // ���� Ÿ�� ����

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

	UpdateHpBar(); // ���� ü�¹� ������Ʈ
	Movement(dt);  // ���� �̵�

	if (health <= 0)
	{
		Die();
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	// ���� �������� ���� �� ü�¹ٰ� ��Ÿ������ ��
	if (health != maxHealth)
	{
		window.draw(hpBarBg);
		window.draw(hpBar);
	}
}

// ���� �ǰ�
void Zombie::OnDamage(int damage)
{
	if (health <= 0)
	{
		health = 0;
		return;
	}

	health -= damage;
}

// ���� Ÿ�� ����
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

// ���� �̵�
void Zombie::Movement(float dt)
{
	// �̵�
	if (Utils::Distance(targetPos, position) > 0.5f)
	{
		SetPosition(position + direction * speed * dt);
	}
	
	// �̵��ϰ��� �ϴ� ������ �ٶ󺸰� ȸ��
	direction = Utils::GetNormal(targetPos - position);
	SetRotation(Utils::Angle(direction));
}

// HP Bar ������Ʈ
void Zombie::UpdateHpBar()
{
	hpBarBg.setPosition(hpBar.getPosition());
	hpBar.setPosition((position.x - GetLocalBounds().width * 0.5f) + hpBarOffset.x, GetGlobalBounds().top - hpBarOffset.y);

	float fill = per * health;
	hpBar.setSize({ fill, 5 });
}

// ��� ó��
void Zombie::Die()
{
	SetActive(false);
}