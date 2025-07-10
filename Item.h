#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	enum ItemType
	{
		HealthPack,
		Ammo,
		count
	};

protected:
	std::string name;
	std::string texId;

public:
	Item(const std::string& name);
	virtual ~Item() = default;
	float lifeTimer = 0.0f;

	virtual void Use() = 0;
};