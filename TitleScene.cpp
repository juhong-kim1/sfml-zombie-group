#include "stdafx.h"
#include "TitleScene.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "DataStruct.h"

void TitleScene::screenchange(const std::string& msg)
{
	if (screen == nullptr) // Check if modetitle is initialized
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
	SpriteGo* bg = new SpriteGo("graphics/background.png", "Background");
	AddGameObject(bg);
	bg->Init();

	DataStruct::DataReset();

	const sf::Texture* bgTex = bg->GetSprite().getTexture();
	if (!bgTex)
	{
		std::cerr << "배경 텍스처가 설정되지 않았습니다!" << std::endl;
		return; // 더 이상 진행하지 않음
	}

	bg->SetOrigin(Origins::TL);
	bg->SetPosition({ 0.f, 0.f });

	//fontIds.push_back("fonts/zombiecontrol.ttf");

	sf::Vector2f winSize = FRAMEWORK.GetWindowSizeF();
	sf::Vector2u texSize = bgTex->getSize();
	bg->SetScale({ winSize.x / texSize.x, winSize.y / texSize.y });

	screen = (TextGo*)AddGameObject(new TextGo("fonts/zombiecontrol.ttf"));
	screen->SetString("Zombie Game");
	screen->SetCharacterSize(90);
	screen->SetFillColor(sf::Color::White);
	screen->SetPosition({ 320.0f, 350.f });

	score = (TextGo*)AddGameObject(new TextGo("fonts/zombiecontrol.ttf"));
	score->SetString("HI SCORE: ");
	score->SetCharacterSize(50);
	score->SetFillColor(sf::Color::White);
	score->SetPosition({ 1350.0f, 30.f });

	clickStart = (TextGo*)AddGameObject(new TextGo("fonts/zombiecontrol.ttf"));
	clickStart->SetString("Click to start");
	clickStart->SetCharacterSize(50);
	clickStart->SetFillColor(sf::Color::White);
	clickStart->SetPosition({ 800.0f, 850.f });



	const sf::Font& font =FONT_MGR.Get("fonts/zombiecontrol.ttf");
	if (FONT_MGR.IsEmpty(font))
	{
		std::cerr << "폰트 로딩 실패: fonts/zombiecontrol.ttf" << std::endl;
	}
	else
	{
		screen->GetText().setFont(font); 
		clickStart->GetText().setFont(font);
		score->GetText().setFont(font);
	}
}

void TitleScene::Update(float dt)
{
	// 마우스 클릭이 들어왔는지 체크 (왼쪽 버튼 클릭)
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// 클릭 좌표 가져오기 (월드 좌표)
		sf::Vector2i mousePos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
		sf::Vector2f worldPos = ScreenToWorld(mousePos);

		// 클릭 시 모드 씬으로 전환
		SCENE_MGR.ChangeScene(SceneIds::Mode);
	}
}

void TitleScene::Draw(sf::RenderWindow& window)  
{  
    Scene::Draw(window);  
}