#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include <SFML\Graphics.hpp>

using namespace sf;

struct AABB
{
	Vector2f min;
	Vector2f max;
};

class Collisions
{
public:
	Collisions();
	~Collisions();
};

#endif