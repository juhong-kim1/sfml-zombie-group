#include "stdafx.h"
#include "ModeScene.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "TitleScene.h"




void ModeScene::SetMode(const std::string& msg)
{
	if (modeselect == nullptr) // Check if modetitle is initialized
	{
		std::cerr << "Error: modetitle is not initialized!" << std::endl;
		return;
	}
}


void ModeScene::Init()
{
	texIds.push_back("graphics/background.png");
	fontIds.push_back("fonts/zombiecontrol.ttf");
	
}
void ModeScene::Enter()
{
	Scene::Enter();
	SpriteGo* bg = new SpriteGo("graphics/background.png", "Background");
	AddGameObject(bg);
	bg->Init();

	const sf::Texture* bgTex = bg->GetSprite().getTexture();
	if (!bgTex)
	{
		std::cerr << "��� �ؽ�ó�� �������� �ʾҽ��ϴ�!" << std::endl;
		return; // �� �̻� �������� ����
	}
	bg->SetOrigin(Origins::TL);
	bg->SetPosition({ 0.f, 0.f });

	sf::Vector2f winSize = FRAMEWORK.GetWindowSizeF();
	sf::Vector2u texSize = bgTex->getSize();
	bg->SetScale({ winSize.x / texSize.x, winSize.y / texSize.y });

	modeselect = (TextGo*)AddGameObject(new TextGo("fonts/zombiecontrol.ttf"));
	modeselect->SetString("1.INCREASED RATE OF FIRE");//1.�߻�ӵ� ����
	modeselect->SetCharacterSize(72);
	modeselect->SetFillColor(sf::Color::White);
	modeselect->SetPosition({ 120.0f, 350.f });

	const sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	//modeselect->GetText().setFont(font);
	std::vector<std::string>messages =
	{
		"1. INCREASED RATE OF FIRE",
		"2. INCREASED CLIF SIZECNEXT RELOAD",
		"3. INCREASED MAX HEALTH",
		"4. INCREASED RUN SPEED",
		"5. MODE AND BATTER HEALTH PICKUPS",
		"6. MODE AND BATTER AMMD PICKUPS",
	};
	float yStart = 300.f;
	float yStep = 70.f;

	for (size_t i = 0; i < messages.size(); ++i)
	{
		TextGo* textObj = (TextGo*)AddGameObject(new TextGo("fonts/zombiecontrol.ttf"));
		textObj->SetString(messages[i]);
		textObj->SetCharacterSize(50);
		textObj->SetFillColor(sf::Color::White);
		textObj->SetPosition({ 120.f, yStart + i * yStep });
		textObj->GetText().setFont(font);
		
		modeOptions.push_back(textObj);
	}
	
	
}



void ModeScene::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2i mousePixelPos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
		sf::Vector2f mouseWorldPos = FRAMEWORK.GetWindow().mapPixelToCoords(mousePixelPos);

		for (size_t i = 0; i < modeOptions.size(); ++i)
		{
			const sf::FloatRect bounds = modeOptions[i]->GetText().getGlobalBounds();

			if (bounds.contains(mouseWorldPos))
			{
				OnOptionClicked(i);  // Ŭ���� �ε��� ����
				break;
			}
		}
	}
	
	/*for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}*/
}
void ModeScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}