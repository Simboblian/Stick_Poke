#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

using namespace sf;

#define SCALE 32.0f

class GameObject
{
protected:
	Vector2f m_Position;
	b2Body* m_Body;

	b2Vec2 SFVECtoB2VEC(Vector2f vector, bool scale = false) { return b2Vec2(vector.x / (scale ? SCALE : 1.f), vector.y / (scale ? SCALE : 1.f)); };
	Vector2f B2VECtoSFVEC(b2Vec2 vector, bool scale = false) { return Vector2f(vector.x * (scale ? SCALE : 1.f), vector.y * (scale ? SCALE : 1.f)); };

	virtual Vector2f GetPosition() { return m_Position; };
	virtual void SetPosition(Vector2f Position) { m_Position = Position; };
public:
	virtual void Draw(RenderWindow &Window);
	virtual void Update();

	GameObject();
	~GameObject();
};

#endif