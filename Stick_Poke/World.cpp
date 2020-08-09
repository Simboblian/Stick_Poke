#include "World.h"

void World::Update()
{
}

void World::Draw(sf::RenderWindow &Window)
{
	for (int i = 0; i < _landList.size(); i++)
		_landList[i]->Draw(Window);
}

World::World()
{
}

sf::Vector2f World::GetCenter()
{
	sf::Vector2f result;

	for (int i = 0; i < _landList.size(); i++)
		result += _landList[i]->GetCenter();

	result = sf::Vector2f(result.x / _landList.size(), result.y / _landList.size());

	return result;
}

World::World(b2World &World, sf::Vector2f Size)
{
	Land *l = new Land(World, Size);
	_landList.push_back(l);
}

World::~World()
{
}
