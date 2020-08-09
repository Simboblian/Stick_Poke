#include "WorldObject.h"

void WorldObject::Draw(sf::RenderWindow & Window)
{
	Window.draw(_rect);
}

void WorldObject::Update(float Delta)
{
	_position = sf::Vector2f(Utility::B2VECtoSFVEC(_body->GetPosition(), true));
	_rect.setPosition(_position);
}

WorldObject::WorldObject(b2World & World, sf::Vector2f Size, sf::Vector2f Position)
{
	_position = Position;

	_rect.setSize(Size);
	_rect.setOrigin(_rect.getSize().x / 2, _rect.getSize().y / 2);
	_rect.setPosition(_position);
	_rect.setFillColor(sf::Color::Red);

	InitSquareBody(World, Size);
	_body->SetTransform(Utility::SFVECtoB2VEC(_position, true), 0);
	_body->SetGravityScale(0.25);
	_body->GetFixtureList()->SetFriction(1);

	_body->SetUserData((void*)ut::b_Doodad);
	_body->GetFixtureList()->SetUserData((void*)ut::f_Hurtbox);
}

WorldObject::WorldObject()
{
}


WorldObject::~WorldObject()
{
}
