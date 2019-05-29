#include "World.h"

void World::Update()
{
}

void World::Draw(sf::RenderWindow &Window)
{
	for (int i = 0; i < m_LandList.size(); i++)
		m_LandList[i]->Draw(Window);
}

World::World()
{
}

sf::Vector2f World::GetCenter()
{
	sf::Vector2f result;

	for (int i = 0; i < m_LandList.size(); i++)
		result += m_LandList[i]->GetCenter();

	result = sf::Vector2f(result.x / m_LandList.size(), result.y / m_LandList.size());

	return result;
}

World::World(sf::Vector2f Size)
{
	Land *l = new Land(Size);
	m_LandList.push_back(l);
}

World::~World()
{
}
