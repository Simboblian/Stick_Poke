#ifndef _INPUT_H
#define _INPUT_H

#include <SFML/Graphics.hpp>
#include "Utility.h"

struct ControlState
{
	bool left;
	bool right;
	bool up;
	bool down;
	bool movement;
	bool stance1;
	bool stance2;
	sf::Vector2f lStick;
	sf::Vector2f rStick;

	ControlState()
	{
	};
};

struct ButtonID
{
	int left;
	int right;
	int up;
	int down;
	int movement;
	int stance1;
	int stance2;
	sf::Joystick::Axis lAxisX;
	sf::Joystick::Axis lAxisY;
	sf::Joystick::Axis rAxisX;
	sf::Joystick::Axis rAxisY;

	ButtonID(int Left, int Right, int Up, int Down, int Movement, int Stance1, int Stance2, sf::Joystick::Axis LX, sf::Joystick::Axis LY, sf::Joystick::Axis RX, sf::Joystick::Axis RY)
	{
		left = Left;
		right = Right;
		up = Up;
		down = Down;
		movement = Movement;
		stance1 = Stance1;
		stance2 = Stance2;
		lAxisX = LX;
		lAxisY = LY;
		rAxisX = RX;
		rAxisY = RY;
	};

	ButtonID()
	{
	};
};

class Input
{
private:
	enum Devices {Controller, MouseKeyboard};
	Devices m_Device = Controller;
	
	int m_ControllerID;

	sf::Vector2f m_MousePos;

	ControlState m_InputState;
	ButtonID m_ButtonID;

	sf::Vector2f MouseToJoystick(sf::RenderWindow &Window, sf::Vector2f ViewPosition);
public:
	void SetBindings(int Left, int Right, int Up, int Down, int Movement, int Stance1, int Stance2, sf::Joystick::Axis LX, sf::Joystick::Axis LY, sf::Joystick::Axis RX, sf::Joystick::Axis RY);
	void TakeInputs(sf::RenderWindow & Window, sf::Vector2f CameraPosition, int ControllerID);
	ControlState ReadInputs();
	ControlState GetInputs() { return m_InputState; };
	void Update(sf::RenderWindow &Window);

	Input();
	~Input();
};

#endif