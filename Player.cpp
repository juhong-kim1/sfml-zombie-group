#include "stdafx.h"
#include "Player.h"
#include "SceneGame1.h"
#include "SceneGame2.h"
#include "SceneGame3.h"
#include "HitBox.h"
#include "Bullet.h"
#include "DataStruct.h"
#include "TileMap.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

int Player::GetReserveAmmo() const
{
	return reserveAmmo;
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
	Scene* currentScene = SCENE_MGR.GetCurrentScene();
	sceneGame1 = dynamic_cast<SceneGame1*>(currentScene);
	sceneGame2 = dynamic_cast<SceneGame2*>(currentScene);
	sceneGame3 = dynamic_cast<SceneGame3*>(currentScene);

	SetStats(); // ���� ����
	ammoInClip = maxClipSize;

	health = maxHealth;

	for (Bullet* bullet : bulletList)
	{
		bullet->SetActive(false);
		bulletPool.push_back(bullet);
	}
	bulletList.clear();

	player.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);

	direction = { 0.f, 0.f };
	look = { 1.f, 1.f };

	shootTimer = 0.f;
	hp = maxHp;
	attackTimer = 0.f;

	// 효과음
	SoundMgr::Instance().Load("shoot", "sound/shoot.wav");
	SoundMgr::Instance().Load("hit", "sound/hit.wav");
	SoundMgr::Instance().Load("reload", "sound/reload.wav");
}

void Player::Update(float dt)
{
	auto it = bulletList.begin();
	while (it != bulletList.end())
	{
		if (!(*it)->GetActive())
		{
			bulletPool.push_back(*it);
			it = bulletList.erase(it);
		}
		else
		{
			++it;
		}
	}

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2f nextPos = position + direction * speed * dt;

	if (!CheckBorder(nextPos))
	{
		// 각 씬별로 TileMap 확인
		bool canMove = false;
		if (sceneGame1)
		{
			canMove = !sceneGame1->GetTileMap()->IsWallAt(nextPos);
		}
		else if (sceneGame2)
		{
			canMove = !sceneGame2->GetTileMap()->IsWallAt(nextPos);
		}
		else if (sceneGame3)
		{
			canMove = !sceneGame3->GetTileMap()->IsWallAt(nextPos);
		}

		if (canMove)
		{
			SetPosition(nextPos);
		}
	}

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos;

	if (sceneGame1)
	{
		mouseWorldPos = sceneGame1->ScreenToWorld(mousePos);
	}
	else if (sceneGame2)
	{
		mouseWorldPos = sceneGame2->ScreenToWorld(mousePos);
	}
	else if (sceneGame3)
	{
		mouseWorldPos = sceneGame3->ScreenToWorld(mousePos);
	}
	else
	{
		// 폴백: 마우스 위치를 그대로 사용
		mouseWorldPos = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	}

	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));

	hitBox.UpdateTransform(player, player.getLocalBounds());

	shootTimer += dt;

	if (InputMgr::GetMouseButton(sf::Mouse::Left) && shootTimer > shootInterval)
	{
		shootTimer = 0.f;
		Shoot();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		Reload();
	}

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(player);
	hitBox.Draw(window);
}

void Player::Shoot()
{
	if (ammoInClip > 0)
	{
		Bullet* bullet = nullptr;
		if (bulletPool.empty())
		{
			bullet = new Bullet();
			bullet->Init();
		}
		else
		{
			bullet = bulletPool.front();
			bulletPool.pop_front();
			bullet->SetActive(true);
		}

		bullet->Reset();
		bullet->Fire(position + look * 10.f, look, 1000.f, 10);
		SoundMgr::Instance().Play("shoot");
		ammoInClip -= 1;
		std::cout << ammoInClip << " / " << reserveAmmo << std::endl;

		bulletList.push_back(bullet);
		
		if (sceneGame1)
		{
			sceneGame1->AddGameObject(bullet);
		}
		else if (sceneGame2)
		{
			sceneGame2->AddGameObject(bullet);
		}
		else if (sceneGame3)
		{
			sceneGame3->AddGameObject(bullet);
		}
	}
}


void Player::RestoreHealth(int amount)
{
	if (health + amount < maxHealth)
	{
		health += amount;
	}
	else
	{
		health = maxHealth;
	}
	std::cout << health << std::endl;
}

void Player::OnDamage(int damage)
{
	if (!isAlive())
	{
		return;
	}

	hp = Utils::Clamp(hp - damage, 0, maxHp);
	SoundMgr::Instance().Play("hit");

	if (hp == 0)
	{
		SCENE_MGR.ChangeScene(SceneIds::Mode);
	}
}

void Player::AddReserveAmmo(int amount)
{
	reserveAmmo += amount;
}

void Player::SetStats()
{
	shootInterval = DataStruct::GetRateOfFire();
	reloadAmount = DataStruct::GetClipSize();
	maxHealth = DataStruct::GetMaxHealth();
	speed = DataStruct::GetRunSpeed();
}

void Player::Reload()
{
	if (ammoInClip + reloadAmount > maxClipSize)
	{
		reserveAmmo = reserveAmmo - (reloadAmount - ammoInClip);
		ammoInClip = maxClipSize;
	}
	else
	{
		ammoInClip = reloadAmount;
		reserveAmmo -= reloadAmount;
	}

	SoundMgr::Instance().Play("reload");
	std::cout << "reload : " << ammoInClip << " / " << reserveAmmo << std::endl;
}
