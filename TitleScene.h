#pragma once
#include "Scene.h"
#include "Framework/TextGo.h"
class TextGo;

class TitleScene :
    public Scene
{
protected:
	int SelectedIndex = 0;
	sf::Sprite spritetitle;
	sf::Sprite spriteMode;
	TextGo* screen;
	TextGo* hiScoreText;
	TextGo* HiScore;
	TextGo* clickStart;

	Gametitle changeScene = Gametitle::mode;

public:
	TitleScene() : Scene(SceneIds::Title) {}
	~TitleScene() override = default;

	void screenchange(const std::string& msg);
	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};