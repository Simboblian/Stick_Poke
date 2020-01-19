#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace ut
{
	const float SCALE = 32.f;
	const float PI = 3.141592653589793f;

	const char* const b_Bullet= "b_Bullet";
	const char* const b_Character = "b_Character";
	const char* const b_Weapon = "b_Weapon";
	const char* const b_Doodad = "b_Doodad";
	const char* const b_Land = "b_Land";

	const char* const f_Hurtbox = "f_Hurtbox";
	const char* const f_Invincible = "f_Invincible";
	const char* const f_Hitbox = "f_Hitbox";
	const char* const f_Foot = "f_Foot";
	const char* const f_Floor = "f_Floor";
	const char* const f_Wall = "f_Wall";
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