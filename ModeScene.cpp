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



	const sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");

	std::vector<std::string>messages =
	{
		"1. INCREASED RATE OF FIRE",
		"2. INCREASED CLIF SIZECNEXT RELOAD",
		"3. INCREASED MAX HEALTH",
		"4. INCREASED RUN SPEED",
		"5. MORE AND BETTER HEALTH PICKUPS",
		"6. MORE AND BETTER AMMO PICKUPS",
	};
	float yStart = 300.f;
	float yStep = 70.f;

	modeOptions.clear();

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
			return;
	}
	
}
void ModeScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void ModeScene::OnOptionClicked(size_t index)
{
	switch (index)
	{
	case 0:
		std::cout << "�߻�ӵ� ���� ��� ���õ�\n";
		//SCENE_MGR.ChangeScene(SceneIds::Game1);  // ����: ���Ӿ����� �̵�
		break;
	case 1:
		std::cout << "źâ ũ�� ���� ��� ���õ�\n";
		break;
	case 2:
		std::cout << "ü�� ���� ��� ���õ�\n";
		break;
	case 3:
		std::cout << "�޸��� �ӵ� ���� ��� ���õ�\n";
		break;
	case 4:
		std::cout << "ü�� ������ ���� ��� ���õ�\n";
		break;
	case 5:
		std::cout << "ź�� ������ ���� ��� ���õ�\n";
		break;
	default:
		break;
	}
}
