#ifndef _LAND_H
#define _LAND_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

#define SIZE 100

class Land : public GameObject
{
private:
	std::vector<sf::RectangleShape*> m_RectList;
	sf::Vector2f m_Position, m_Origin, m_Size, m_Center;
	sf::Color m_Color1 = sf::Color::Magenta, m_Color2 = sf::Color::Blue;

public:
	void SetState(state State) { m_State = IDLE; };

	std::vector<sf::RectangleShape*> GetRectList() { return m_RectList; };
	sf::Vector2f GetPosition() { return m_Position; };
	sf::Vector2f GetCenter() { return m_Center; };
	sf::RectangleShape GetShape();

	void Draw(sf::RenderWindow &Window);
	void Update(sf::Vector2f Gravity);

	Land(sf::Vector2f Size);
	Land();
	~Land();
};

#endif
