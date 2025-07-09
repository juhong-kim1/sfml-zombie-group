#include "stdafx.h"
#include "effect.h"


	void effect::Init()
	{
		//TileMap 생성 및 추가
		//tileMap = new TileMap("EffectMap");
		//tileMap->SceneId = effectType;
		//AddGameObject(tileMap);

		player = new Player();
		AddGameObject(player);//씬 등록

		switch (effectType)
		{
		case SceneIds::Game1:
			player->Effect1();
			break;
		case SceneIds::Game2:
			player->Effect2();
			break;
		case SceneIds::Game3:
			player->Effect3();
			break;
		case SceneIds::Game4:
			player->Effect4();
			break;
		case SceneIds::Game5:
			player->Effect5();
			break;
		case  SceneIds::Game6:
			player->Effect6();
		default:
			break;
		}
	}
	
	