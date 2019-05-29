#ifndef _WORLD_H
#define _WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Land.h"

class World
{
private:
	std::vector<Land*> m_LandList;

public:
	void Update();
	void Draw(sf::RenderWindow &Window);
	std::vector<Land*> GetLandList() { return m_LandList; };

	sf::Vector2f GetCenter();

	World(sf::Vector2f Size);
	World();
	~World();
};

#endif // !_WORLD_H
