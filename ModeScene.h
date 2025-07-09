#pragma once
#include "Scene.h"
#include "Framework/TextGo.h"
#include "TitleScene.h"
class TextGo;

class ModeScene :public Scene
{protected:
	std::vector<TextGo*> modeOptions;
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

	Gametitle changeScene = Gametitle::title;

public:
	ModeScene() :Scene(SceneIds::Mode) {}
	~ModeScene() override = default;

	void SetMode(const std::string& msg);
	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
	void Exit()override;

	void OnOptionClicked(size_t index);//클릭 콜백 함수
};