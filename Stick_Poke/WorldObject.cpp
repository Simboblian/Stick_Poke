#include "WorldObject.h"

void WorldObject::Draw(sf::RenderWindow & Window)
{
	Window.draw(m_Rect);
}

void WorldObject::Update()
{
	m_Position = sf::Vector2f(Utility::B2VECtoSFVEC(m_Body->GetPosition(), true));
	m_Rect.setPosition(m_Position);
}

WorldObject::WorldObject(b2World & World, sf::Vector2f Size, sf::Vector2f Position)
{
	m_Position = Position;

	m_Rect.setSize(Size);
	m_Rect.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_Rect.setPosition(m_Position);
	m_Rect.setFillColor(sf::Color::Red);

	InitSquareBody(World, Size);
	m_Body->SetTransform(Utility::SFVECtoB2VEC(m_Position, true), 0);
	m_Body->SetGravityScale(0.25);
	m_Body->GetFixtureList()->SetFriction(1);

	m_Body->SetUserData((void*)ut::b_Doodad);
	m_Body->GetFixtureList()->SetUserData((void*)ut::f_Hurtbox);
}

WorldObject::WorldObject()
{
}


WorldObject::~WorldObject()
{
}
