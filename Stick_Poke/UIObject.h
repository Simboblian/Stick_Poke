#ifndef _UIOBJECT_H
#define _UIOBJECT_H

#include <SFML/Graphics.hpp>

class UIObject
{
protected:
	sf::Vector2f m_Position;
	sf::Vector2f m_Size;

public:
	virtual void SetSize(sf::Vector2f Size) { m_Size = Size; };
	sf::Vector2f GetSize() { return m_Size; };

	virtual void SetPosition(sf::Vector2f Position) { m_Position = Position; };
	sf::Vector2f GetPosition() { return m_Position; };

	virtual void Update() {};
	virtual void Draw() {};

	UIObject();
	~UIObject();
};

#endif