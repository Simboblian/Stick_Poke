#ifndef _UIOBJECT_H
#define _UIOBJECT_H

#include <SFML/Graphics.hpp>

class UIObject
{
protected:
	sf::Vector2f _position;
	sf::Vector2f _size;

public:
	virtual void SetSize(sf::Vector2f Size) { _size = Size; };
	sf::Vector2f GetSize() { return _size; };

	virtual void SetPosition(sf::Vector2f Position) { _position = Position; };
	sf::Vector2f GetPosition() { return _position; };

	virtual void Update() {};
	virtual void Draw() {};

	UIObject();
	~UIObject();
};

#endif