﻿#include "stdafx.h"
#include "effect.h"


	void effect::Init()
	{


		player = new Player();
		AddGameObject(player);//씬 등록

		switch (effectType)
		{
		case SceneIds::Game1:
			break;
		case SceneIds::Game2:
			break;
		case SceneIds::Game3:
			break;
		case SceneIds::Game4:
			break;
		case SceneIds::Game5:
			break;
		case  SceneIds::Game6:
		default:
			break;
		}
	}
	
	