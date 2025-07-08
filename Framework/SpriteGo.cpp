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
		std::cerr << "SpriteGo::Init - 텍스처 로딩 실패: " << textureId << std::endl;
	}
	
	sprite.setTexture(tex);
	// Reset();
	// 
	// 원본 크기로 출력하려면 스케일 초기화 필요
	sprite.setScale(1.f, 1.f);

	// 위치도 기본값 (0,0)으로 맞추거나 원하는 값으로
	sprite.setPosition(0.f, 0.f);

	active = true; 

}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{

	const sf::Texture& tex = TEXTURE_MGR.Get(textureId);
	if (&tex == &ResourceMgr<sf::Texture>::Empty) // 비교 가능
	{
		std::cerr << "SpriteGo::Reset - 텍스처가 로딩되지 않았습니다: " << textureId << std::endl;
	}
	sprite.setTexture(tex);
	// 원본 크기 유지용 스케일 초기화
	sprite.setScale(1.f, 1.f);
	sprite.setPosition(position); // 유지했던 위치로 다시 설정
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
