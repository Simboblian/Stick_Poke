#include "Character.h"

void Character::Draw(sf::RenderWindow &Window)
{
	Window.draw(m_Rect);
	m_Weapon->Draw(Window, true);
}

void Character::Update(sf::Vector2f Gravity)
{
	sf::Vector2f old_Velocity = m_Velocity;
	if (m_State == STANDING)
		m_Velocity = sf::Vector2f(0, 0);
	else
		m_Velocity = Gravity;

	//if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -20.0f)
	//	m_Velocity.x += -1.0f;
	//else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 20.0f)
	//	m_Velocity.x += 1.0f;
	//else
	//	m_Velocity.x = 0.0f;

	//sf::Vector2f controller;
	//controller.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U);
	//controller.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V);
	
	m_Position += m_Velocity;

	m_Rect.setPosition(m_Position);

	m_Weapon->Update(sf::Vector2f(0, 0), m_Position, false, false);
}

Character::Character()
{
	m_GravityScale = 1;

	m_Rect.setSize(sf::Vector2f(50.0f, 100.0f));
	m_Rect.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_Rect.setPosition(m_Position);
	m_Rect.setFillColor(sf::Color::Yellow);

	m_BackBicep.setSize(sf::Vector2f(10.0f, 40.0f));
	m_BackBicep.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_BackBicep.setPosition(m_Position);
	m_BackBicep.setFillColor(sf::Color::Red);

	m_BackBicep.setSize(sf::Vector2f(10.0f, 40.0f));
	m_BackForearm.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_BackForearm.setPosition(m_Position);
	m_BackForearm.setFillColor(sf::Color::Red);
	
	m_Weapon = new Weapon();
	m_Weapon->SetAnchorOffset(sf::Vector2f(-75.0, 15.0f));
	m_Weapon->SetControlRadius(50.0f);
	m_Weapon->SetControlOffset(sf::Vector2f(75.0f, 0.0f));
	m_Weapon->SetWeaponSize(sf::Vector2f(180.0, 10.0f));
	m_Weapon->SetWeaponOrigin(sf::Vector2f(160.0, 5.0f));
	m_Weapon->SetHitboxOffset(sf::Vector2f(15.0, 0.0f));
	m_Weapon->SetHitboxRadius(7.5f);

	m_State = IDLE;
}

Character::~Character()
{
}
