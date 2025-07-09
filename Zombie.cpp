#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"

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
	target = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	SetRandomType(); // 랜덤 타입 설정
	hitBoxActive = true;

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	sprite.setColor(sf::Color(255, 255, 255, 255));

	SetOrigin(Origins::MC);
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
	UpdateHpBar(); // 좀비 체력바 업데이트
	Movement(dt);  // 좀비 이동
	//Attack(dt);    // 공격

	if (health <= 0)
	{
		Die();
	}

	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());

	if (!isAlive)
	{
		fadeTimer += dt;
		float a = Utils::Lerp(1.0f, 0.0f, fadeTimer / 5.0f, true);
		sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(a * 255)));
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	// 최초 데미지를 입은 후 체력바가 나타나도록 함
	if (health != maxHealth && isAlive)
	{
		window.draw(hpBarBg);
		window.draw(hpBar);
	}

	hitBox.Draw(window);
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

// 좀비 공격
void Zombie::Attack(float dt)
{
	attackTimer += dt;
	if (attackInterval < attackTimer && Utils::CheckCollision(hitBox.rect, target->GetHitBox().rect)) // 플레이어랑 병합 후 충돌체크하여 공격 **
	{
		attackTimer = 0;
		// 플레이어 데미지 메서드 호출
		target->OnDamage(damage);
		std::cout << "공격" << std::endl;
	}
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
	if (isAlive)
	{
		//이동하고자 하는 방향을 바라보게 회전
		direction = Utils::GetNormal(target->GetPosition() - position);
		SetRotation(Utils::Angle(direction));

		// 이동
		if (Utils::Distance(target->GetPosition(), position) > 0.5f)
		{
			SetPosition(position + direction * speed * dt);
		}
	}
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
	// 사망 이펙트
	isAlive = false;
	sprite.setTexture(TEXTURE_MGR.Get(bloodTexId), true);
	SetRotation(0.f);

	// 피가 될 경우 레이어 변경
	sortingLayer = SortingLayers::Background;
	sortingOrder = 1;
	hitBoxActive = false;
}