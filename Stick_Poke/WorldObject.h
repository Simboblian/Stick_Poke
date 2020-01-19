#ifndef _WORLDOBJECT_H
#define _WORLDOBJECT_H

#include "GameObject.h"

class WorldObject : public GameObject
{
private:
	sf::RectangleShape m_Rect;
public:
	void Draw(sf::RenderWindow &Window);
	void Update();

	WorldObject(b2World &World, sf::Vector2f Size, sf::Vector2f Position);
	WorldObject();
	~WorldObject();
};

#endif