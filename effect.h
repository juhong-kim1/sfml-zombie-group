#pragma once
#include "Scene.h"
#include "Player.h"
#include "TileMap.h"


class effect :
    public Scene
{
protected:
    SceneIds effectType;
	TileMap* tileMap = nullptr;
	Player* player = nullptr;
public:
	effect(SceneIds id) : Scene(id), effectType(id) {}

	void SetPlayer(Player* p)
	{
		player = p;
		AddGameObject(player);
	}


	void Init() override;

	
};

