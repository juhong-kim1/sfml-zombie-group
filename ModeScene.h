#pragma once
#include "Scene.h"
#include "Framework/TextGo.h"
#include "TitleScene.h"
class TextGo;
enum class GameMode
{
	title,
	one,
	two,
	three,
	four,
	five,
	six
};
class ModeScene :public Scene
{protected:
	TextGo* modeselect;
	sf::Texture tex1;
	sf::Texture tex2;
	sf::Texture tex3;
	sf::Texture tex4;
	sf::Texture tex5;
	sf::Texture tex6;

	TextGo* Textgo_1;
	TextGo* Textgo_2;
	TextGo* Textgo_3;
	TextGo* Textgo_4;
	TextGo* Textgo_5;
	TextGo* Textgo_6;
public:
	ModeScene() :Scene(SceneIds::Mode) {}
	~ModeScene() override = default;

	void SetMode(const std::string& msg);
	void Init() override;
	void Enter() override;

	void Update(float dt) override;

};

