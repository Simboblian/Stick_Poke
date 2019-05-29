#ifndef _COLLISIONHANDLER_H
#define _COLLISIONHANDLER_H

#include <SFML\Graphics.hpp>

static class CollisionHandler
{
private:
	static float GetMagnitude(sf::Vector2f v) { return sqrt((v.x * v.x) + (v.y * v.y)); };

	//std::map<GameObject, GameObject> collidingObjects;
public:
	static bool CirclePoint(sf::CircleShape circle, sf::Vector2f point);
	static bool CircleCircle(sf::CircleShape circleA, sf::CircleShape circleB);
	static bool RectPoint(sf::RectangleShape rect, sf::Vector2f point);
	static bool RectRect(sf::RectangleShape rectA, sf::RectangleShape rectB);

	CollisionHandler();
	~CollisionHandler();
};

#endif