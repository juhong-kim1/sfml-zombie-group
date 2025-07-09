#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	tileTypes.clear();
	tileTypes.resize(count.x * count.y);

	sf::Vector2f posOffset[4] =
	{
		{ 0.f, 0.f },
		{ size.x, 0.f },
		{ size.x, size.y },
		{ 0.f, size.y },
	};

	sf::Vector2f texCoords[4] =
	{
		{ 0.f, 0.f },
		{ 50.f, 0.f },
		{ 50.f, 50.f },
		{ 0.f, 50.f },
	};

	for (int i = 0; i < count.y; ++i)
	{

		for (int j = 0; j < count.x; ++j)
		{
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}

			int quadIndex = i * count.x + j;

			tileTypes[quadIndex] = texIndex;
			sf::Vector2f quadPos(j * size.x, i * size.y);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + posOffset[k];
				va[vertexIndex].texCoords = texCoords[k];
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}

		}
	}
}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void TileMap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}
	UpdateTransform();
}

bool TileMap::IsWallAt(const sf::Vector2f& worldPos)
{

	sf::Vector2f localPos = transform.getInverse().transformPoint(worldPos);

	int x = static_cast<int>(localPos.x / cellSize.x);
	int y = static_cast<int>(localPos.y / cellSize.y);



	if (x < 0 || y < 0 || x >= cellCount.x || y >= cellCount.y)
	{
		return true;
	}

	int index = y * cellCount.x + x;


	return tileTypes[index] == 3;
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	SceneId = SceneIds::Game1;
	SceneOrder = 0;

	Set({ 50, 50 }, { 50.f, 50.f });
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);

	SetOrigin(Origins::MC);
	SetScale({ 1.f, 1.f });
	SetPosition({ 0.f, 0.f });
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
}