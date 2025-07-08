#include "stdafx.h"
#include "ModeScene.h"
#include "Framework/TextGo.h"
#include "SpriteGo.h"
#include "TitleScene.h"



void ModeScene::SetMode(const std::string& msg)
{

}


void ModeScene::Init()
{
	modeselect = (TextGo*)AddGameObject(new TextGo("fonts/KOMIKAP_.ttf"));
	modeselect->SetString("TIMBER GAME");
	modeselect->SetCharacterSize(72);
	modeselect->SetFillColor(sf::Color::White);
	modeselect->SetPosition({ 720.0f, 350.f });
	
}
void Enter()
{

}

void Update(float dt)
{

}