#include "stdafx.h"
#include "SpriteGo.h"
#include "Scene.h"

SpriteGo::SpriteGo(const std::string& texPlayerId, const std::string& name)
	: GameObject(name), textureId(texPlayerId)
{
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(pos);
}

void SpriteGo::SetRotation(float rot)
{
	rotation = rot;
	sprite.setRotation(rotation);
}

void SpriteGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	sprite.setScale(scale);
}

void SpriteGo::SetOrigin(const sf::Vector2f& o)
{
	originPreset = Origins::Custom;
	origin = o;
	sprite.setOrigin(o);
}

void SpriteGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(sprite, originPreset);
	}

}

void SpriteGo::Init()
{
	const sf::Texture& tex = TEXTURE_MGR.Get(textureId);
	
	if (TEXTURE_MGR.IsEmpty(tex)) 
	{
		std::cerr << "SpriteGo::Init - �ؽ�ó �ε� ����: " << textureId << std::endl;
	}
	
	sprite.setTexture(tex);
	// Reset();
	// 
	// ���� ũ��� ����Ϸ��� ������ �ʱ�ȭ �ʿ�
	sprite.setScale(1.f, 1.f);

	// ��ġ�� �⺻�� (0,0)���� ���߰ų� ���ϴ� ������
	sprite.setPosition(0.f, 0.f);

	active = true; 

}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{

	const sf::Texture& tex = TEXTURE_MGR.Get(textureId);
	if (&tex == &ResourceMgr<sf::Texture>::Empty) // �� ����
	{
		std::cerr << "SpriteGo::Reset - �ؽ�ó�� �ε����� �ʾҽ��ϴ�: " << textureId << std::endl;
	}
	sprite.setTexture(tex);
	// ���� ũ�� ������ ������ �ʱ�ȭ
	sprite.setScale(1.f, 1.f);
	sprite.setPosition(position); // �����ߴ� ��ġ�� �ٽ� ����
	Utils::SetOrigin(sprite, originPreset);

}

void SpriteGo::Update(float dt)
{

}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(sprite);
	}
}
