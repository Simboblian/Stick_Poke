#ifndef _WORLD_H
#define _WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Land.h"

class World
{
private:
	std::vector<Land*> _landList;

public:
	void Update();
	void Draw(sf::RenderWindow &Window);
	std::vector<Land*> GetLandList() { return _landList; };

	sf::Vector2f GetCenter();

	World(b2World &World, sf::Vector2f Size);
	World();
	~World();
};

#endif // !_WORLD_H
