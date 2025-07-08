#include "stdafx.h"
#include "TitleScene.h"
#include "SpriteGo.h"
#include "TextGo.h"


void TitleScene::screenchange(const std::string& msg)
{
	if (screenselect == nullptr) // Check if modetitle is initialized
	{
		std::cerr << "Error: modetitle is not initialized!" << std::endl;
		return;
	}
}


void TitleScene::Init()
{

	texIds.push_back("graphics/background.png");
	fontIds.push_back("fonts/zombiecontrol.ttf");

}
void TitleScene::Enter()
{
	Scene::Enter();
	//texIds.push_back("graphics/background.png");
	SpriteGo* bg = new SpriteGo("graphics/background.png", "Background");
	AddGameObject(bg);
	bg->Init();

	if (!bg->GetSprite().getTexture()) {
		std::cerr << "배경 텍스처 로딩 실패!" << std::endl;
	}


	fontIds.push_back("fonts/zombiecontrol.ttf");

	screenselect = (TextGo*)AddGameObject(new TextGo("fonts/zombiecontrol.ttf"));
	screenselect->SetString("Zombie Game");
	screenselect->SetCharacterSize(72);
	screenselect->SetFillColor(sf::Color::White);
	screenselect->SetPosition({ 720.0f, 350.f });

}


void TitleScene::Update(float dt)
{

}
void TitleScene::Draw(sf::RenderWindow& window)  
{  
    Scene::Draw(window);  
}