#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame1.h"
#include "SceneGame2.h"
#include "SceneGame3.h"
#include "GameData.h"

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
	hitBoxActive = true;
	isAlive = true;
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	target = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");
	SoundMgr::Instance().Load("splat", "Sound/splat.wav");

	SetRandomType(); // ���� Ÿ�� ����

	isAlive = true;
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

	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());
}

void Zombie::Update(float dt)
{
	attackTimer += dt;

	UpdateHpBar(); // ���� ü�¹� ������Ʈ
	Movement(dt);  // ���� �̵�
	Attack(dt);    // ���� ����

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

	// ���� �������� ���� �� ü�¹ٰ� ��Ÿ������ ��
	if (health != maxHealth && isAlive)
	{
		window.draw(hpBarBg);
		window.draw(hpBar);
	}

	hitBox.Draw(window);
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
	SoundMgr::Instance().Play("splat");
}

// ���� ����
void Zombie::Attack(float dt)
{
	attackTimer += dt;

	if (!isAlive)
	{
		return;
	}

	if (attackInterval < attackTimer && Utils::CheckCollision(hitBox.rect, target->GetHitBox().rect))
	{
		attackTimer = 0;
		target->OnDamage(damage);
		std::cout << "����" << std::endl;
	}
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
		damage = 10;
	}
	else if (random == (int)Type::chaser)
	{
		texId = "graphics/chaser.png";
		maxHealth = 100;
		speed = 150.f;
		damage = 10;
	}
	else if (random == (int)Type::crawler)
	{
		texId = "graphics/crawler.png";
		maxHealth = 100;
		speed = 30.0f;
		damage = 10;
	}
	
	sprite.setTexture(TEXTURE_MGR.Get(texId), true);

	health = maxHealth;
}

// ���� �̵�
void Zombie::Movement(float dt)
{
	if (isAlive)
	{
		//�̵��ϰ��� �ϴ� ������ �ٶ󺸰� ȸ��
		direction = Utils::GetNormal(target->GetPosition() - position);
		SetRotation(Utils::Angle(direction));

		// �̵�
		if (Utils::Distance(target->GetPosition(), position) > 0.5f)
		{
			sf::Vector2f nextPos = position + direction * speed * dt;

	
			Scene* currentScene = SCENE_MGR.GetCurrentScene();
			TileMap* tileMap = nullptr;

			if (auto sceneGame1 = dynamic_cast<SceneGame1*>(currentScene))
			{
				tileMap = sceneGame1->GetTileMap();
			}
			else if (auto sceneGame2 = dynamic_cast<SceneGame2*>(currentScene))
			{
				tileMap = sceneGame2->GetTileMap();
			}
			else if (auto sceneGame3 = dynamic_cast<SceneGame3*>(currentScene))
			{
				tileMap = sceneGame3->GetTileMap();
			}

			// ���� �ƴ� �����θ� �̵�
			if (tileMap && !tileMap->IsWallAt(nextPos))
			{
				SetPosition(nextPos);
			}
			else
			{
				// ���� ������ �� �ٸ� ���� �õ� (�ɼ�)
				// X�ุ �̵� �õ�
				sf::Vector2f altPos1 = sf::Vector2f(nextPos.x, position.y);
				if (tileMap && !tileMap->IsWallAt(altPos1))
				{
					SetPosition(altPos1);
				}
				// Y�ุ �̵� �õ�
				else
				{
					sf::Vector2f altPos2 = sf::Vector2f(position.x, nextPos.y);
					if (tileMap && !tileMap->IsWallAt(altPos2))
					{
						SetPosition(altPos2);
					}
				}
				// �� �� �������� �̵����� ����
			}
		}
	
	}
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
	if (!isAlive) return;
	SceneGame1* gameScene = dynamic_cast<SceneGame1*>(parentScene);
	
	// ��� ����Ʈ
	isAlive = false;
	sprite.setTexture(TEXTURE_MGR.Get(bloodTexId), true);
	SetRotation(0.f);
	sortingLayer = SortingLayers::Background;
	sortingOrder = 1;
	hitBoxActive = false;

	if (parentScene != nullptr)
	{
		SceneGame1* gameScene = dynamic_cast<SceneGame1*>(parentScene);
		if (gameScene != nullptr)
		{
			gameScene->AddScore(100); // 100�� �߰�
		}
	}
}

void Zombie::SetParentScene(Scene* scene)
{
	parentScene = scene;
}


