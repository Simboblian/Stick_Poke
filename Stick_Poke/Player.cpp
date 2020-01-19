#include "Player.h"

void Player::Initialize()
{
}

void Player::ProcessInputs(sf::RenderWindow &Window)
{
	m_Input->TakeInputs(Window, m_Character.GetPosition(), 0);
	m_Character.ReceiveInputs(m_Input);
}

void Player::Update(sf::RenderWindow &Window)
{
	m_Camera->SetPosition(m_Character.GetPosition());
	m_Camera->Update(Window);
	m_Input->Update(Window, m_Character.GetPosition(), m_Camera->GetCamera().getCenter());
}


Player::Player(Character & Char, sf::Vector2f CameraSize) : m_Character(Char)
{
	m_Camera = new Camera(CameraSize);
	m_Input = new Input();
	m_Input->SetBindings(4, 5, 6, 7, 3, 0, 1, 2, 10, 8, 9, sf::Joystick::Axis::X, sf::Joystick::Axis::Y, sf::Joystick::Axis::U, sf::Joystick::Axis::V); //These values are just whatevs atm.
}

Player::Player() : m_Character(Character())
{
	m_Input = new Input();
	m_Camera = new Camera(sf::Vector2f(0, 0));
	m_Input->SetBindings(4, 5, 6, 7, 3, 0, 1, 2, 10, 8, 9, sf::Joystick::Axis::X, sf::Joystick::Axis::Y, sf::Joystick::Axis::U, sf::Joystick::Axis::V); //These values are just whatevs atm.
}

Player::~Player()
{
}
