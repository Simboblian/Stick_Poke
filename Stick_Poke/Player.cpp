#include "Player.h"

void Player::Initialize()
{
}

void Player::ProcessInputs(sf::RenderWindow &Window)
{
	_input->TakeInputs(Window, _character.GetPosition(), 0);
	_character.ReceiveInputs(_input);
}

void Player::Update(sf::RenderWindow &Window)
{
	_camera->SetPosition(_character.GetPosition());
	_camera->Update(Window);
	_input->Update(Window, _character.GetPosition(), _camera->GetCamera().getCenter());
}


Player::Player(Character & Char, sf::Vector2f CameraSize) : _character(Char)
{
	_camera = new Camera(CameraSize);
	_input = new Input();
	_input->SetBindings(4, 5, 6, 7, 3, 0, 1, 2, 10, 8, 9, sf::Joystick::Axis::X, sf::Joystick::Axis::Y, sf::Joystick::Axis::U, sf::Joystick::Axis::V); //These values are just whatevs atm.
}

Player::Player() : _character(defaultChar)
{
	_input = new Input();
	_camera = new Camera(sf::Vector2f(0, 0));
	_input->SetBindings(4, 5, 6, 7, 3, 0, 1, 2, 10, 8, 9, sf::Joystick::Axis::X, sf::Joystick::Axis::Y, sf::Joystick::Axis::U, sf::Joystick::Axis::V); //These values are just whatevs atm.
}

Player::~Player()
{
}
