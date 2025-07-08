#pragma once
#include "GameObject.h"

class Item : public GameObject
{
protected:
	std::string name;
	std::string texId;

public:
	Item(const std::string& name);
	virtual ~Item() = default;

	virtual void Use() = 0;
};