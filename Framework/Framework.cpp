#include "stdafx.h"
#include "Framework.h"

void Framework::Init(int w, int h, const std::string& t)
{   
    // 전체화면 모드로 데스크탑 해상도 사용
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // 전체화면으로 창 생성
	//window.create(sf::VideoMode(w, h), t);
    window.create(desktop, t, sf::Style::Fullscreen);
    std::vector<std::string> texIds 
    = { "graphics/background.png", "graphics/player.png" };

    /*window.create(desktop, "Zombie Game", sf::Style::Fullscreen);*/

	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);

    Utils::Init();
	InputMgr::Init();
	SCENE_MGR.Init();
}

void Framework::Do()
{
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        realDeltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        time += deltaTime;
        realTime = realDeltaTime;

        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //esc 누르면 창 닫기
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            InputMgr::UpdateEvent(event);
        }

        InputMgr::Update(deltaTime);

        // Update

#ifdef DEF_DEV
        if (InputMgr::GetKeyDown(sf::Keyboard::F10))
        {
            Variables::isDrawHitBox = !Variables::isDrawHitBox;
        }
#endif


        SCENE_MGR.Update(deltaTime);

        // Draw
        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
	SCENE_MGR.Release();

	SOUNDBUFFER_MGR.Unload(soundIds);
	FONT_MGR.Unload(fontIds);
	TEXTURE_MGR.Unload(texIds);
}
