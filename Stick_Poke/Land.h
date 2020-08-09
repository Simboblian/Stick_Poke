#ifndef _LAND_H
#define _LAND_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameObject.h"

#define SIZE 100

class Land : public GameObject
{
private:
	std::vector<sf::RectangleShape*> _rectList;
	sf::Vector2f _origin, _size, _center;
	sf::Color _color1 = sf::Color::Magenta, _color2 = sf::Color::Blue;

public:
	void SetState(state State) { _state = IDLE; };

	std::vector<sf::RectangleShape*> GetRectList() { return _rectList; };
	sf::Vector2f GetCenter() { return _center; };
	sf::RectangleShape GetShape();

	void Draw(sf::RenderWindow &Window);
	void Update(float Delta);

	Land(b2World &World, sf::Vector2f Size);
	Land();
	~Land();
};

#endif
