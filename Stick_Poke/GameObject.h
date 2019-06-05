#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utility.h"

enum state { IDLE, HIT, STANDING, AIRBORNE };

class GameObject
{
protected:
	state m_State;

	b2Body *m_Body;

	float m_GravityScale;

	sf::Vector2f m_Position;

	virtual void CreateRoundedBody(b2World &World, sf::Vector2f Size);
	virtual void CreateSquareBody(b2World &World, sf::Vector2f Size);
	virtual void CreateCircularBody(b2World &World, float Radius);
	virtual void CreateRoundedFixture(sf::Vector2f Size);
	virtual void CreateSquareFixture(sf::Vector2f Size);
	virtual void CreateCircleFixture(float Radius);
public:
	//- OBJECT BASICS -//
	virtual void Draw(sf::RenderWindow &Window);
	virtual void Update();
	virtual void Update(sf::Vector2f Gravity);
	//----- SETS -----//
	virtual void SetState(state State) { m_State = State; };
	virtual void SetPosition(sf::Vector2f Position) { m_Position = Position; m_Body->SetTransform(Utility::SFVECtoB2VEC(m_Position, true), 0); };
	virtual void SetPosition(b2Vec2 Position) { m_Position = Utility::B2VECtoSFVEC(Position, true); m_Body->SetTransform(Position, 0); };
	//----- GETS -----//
	virtual sf::Vector2f GetPosition() { return Utility::B2VECtoSFVEC(m_Body->GetPosition(), true); };
	virtual float GetGravityScale() { return m_GravityScale; };
	virtual sf::RectangleShape GetShape() { return sf::RectangleShape(); };
	virtual b2Body* GetBody() { return m_Body; };
	//- CONSTRUCTORS -//
	GameObject();
	~GameObject();
};

#endif