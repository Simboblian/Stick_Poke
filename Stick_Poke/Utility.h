#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace ut
{
	const float SCALE = 32.f;
	const float PI = 3.141592653589793f;
};

class Utility
{
private:
	Utility() {};
	~Utility() {};

public:
	static float GetMagnitude(sf::Vector2f v) { return sqrt((v.x * v.x) + (v.y * v.y)); };
	static sf::Vector2f Normalise(sf::Vector2f v)
	{
		float length = GetMagnitude(v);
		if (length != 0)
			return sf::Vector2f(v.x / length, v.y / length);
		else
			return v;
	}

	static sf::Vector2f Truncate(sf::Vector2f v, float max)
	{
		if (GetMagnitude(v) > max)
		{
			v = Normalise(v);

			return sf::Vector2f(v.x * max, v.y * max);
		}

		return v;
	}

	static sf::Vector2f MidPointOfTwoVectors(sf::Vector2f firstPoint, sf::Vector2f secondPoint)
	{
		return sf::Vector2f((firstPoint.x + secondPoint.x) / 2, (firstPoint.y + secondPoint.y) / 2);
	}

	static float AngleBetweenTwoVectors(sf::Vector2f firstPoint, sf::Vector2f secondPoint)
	{
		return atan((secondPoint.y - firstPoint.y) / (secondPoint.x - firstPoint.x));
	}

	static float DEGTORAD(float degrees) { return (degrees * ut::PI) / 180; };
	static float RADTODEG(float radians) { return (radians * 180) / ut::PI; };

	static float ScaleToB2(float number) { return number / ut::SCALE; };
	static float ScaleFromB2(float number) { return number * ut::SCALE; };

	static b2Vec2 SFVECtoB2VEC(sf::Vector2f vector, bool scale = false) { return b2Vec2(vector.x / (scale ? ut::SCALE : 1.f), vector.y / (scale ? ut::SCALE : 1.f)); };
	static sf::Vector2f B2VECtoSFVEC(b2Vec2 vector, bool scale = false) { return sf::Vector2f(vector.x * (scale ? ut::SCALE : 1.f), vector.y * (scale ? ut::SCALE : 1.f)); };
};

#endif