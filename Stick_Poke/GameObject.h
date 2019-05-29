#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <SFML/Graphics.hpp>

enum state { IDLE, HIT, STANDING, AIRBORNE };

class GameObject
{
protected:
	state m_State;

	float m_GravityScale;

	sf::Vector2f m_Position;

	virtual sf::Vector2f GetPosition() { return m_Position; };
	virtual void SetPosition(sf::Vector2f Position) { m_Position = Position; };
public:
	virtual void Draw(sf::RenderWindow &Window);
	virtual void Update();
	virtual void Update(sf::Vector2f Gravity);
	virtual void SetState(state State) { m_State = State; };
	virtual float GetGravityScale() { return m_GravityScale; };
	virtual sf::RectangleShape GetShape() { return sf::RectangleShape(); };

	GameObject();
	~GameObject();
};

#endif