#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Utility.h"

enum state { IDLE, HIT, STANDING, AIRBORNE };

class GameObject
{
private:
	virtual void CreateRoundedFixture(sf::Vector2f Size);
	virtual void CreateSquareFixture(sf::Vector2f Size);
	virtual void CreateCircleFixture(float Radius);
protected:
	state _state;

	b2Body *_body;

	sf::Vector2f _position;

	virtual void InitRoundedBody(b2World &World, sf::Vector2f Size);
	virtual void InitSquareBody(b2World &World, sf::Vector2f Size);
	virtual void InitCircularBody(b2World &World, float Radius);
public:

	//- OBJECT BASICS -//
	virtual void Draw(sf::RenderWindow &Window);
	virtual void Update(float Delta);
	//----- SETS -----//
	virtual void SetState(state State) { _state = State; };
	virtual void SetPosition(sf::Vector2f Position) { _position = Position; _body->SetTransform(Utility::SFVECtoB2VEC(_position, true), 0); };
	virtual void SetPosition(b2Vec2 Position) { _position = Utility::B2VECtoSFVEC(Position, true); _body->SetTransform(Position, 0); };
	//----- GETS -----//
	virtual sf::Vector2f GetPosition() { return Utility::B2VECtoSFVEC(_body->GetPosition(), true); };
	virtual sf::Vector2f GetHitVector() { return sf::Vector2f(0, 0); };
	virtual sf::RectangleShape GetShape() { return sf::RectangleShape(); };
	virtual b2Body* GetBody() { return _body; };
	//- CONSTRUCTORS -//
	GameObject();
	~GameObject();
};

#endif