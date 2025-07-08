#pragma once
#include "GameObject.h"
class TileMap :
    public GameObject
{
protected:
    sf::VertexArray va;
    std::string spriteSheetId = "graphics/background.png";

};

