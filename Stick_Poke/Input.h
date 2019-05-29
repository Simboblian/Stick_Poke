#ifndef _INPUT_H
#define _INPUT_H

#include <SFML/Graphics.hpp>

struct ControllerState
{
	bool left;
	bool right;
	bool dash_left;
	bool dash_right;
	bool stance1;
	bool stance2;
	sf::Vector2f lStick;
	sf::Vector2f rStick;

	ControllerState()
	{
	};
};

struct ButtonID
{
	int left;
	int right;
	int dash_left;
	int dash_right;
	int stance1;
	int stance2;
	sf::Joystick::Axis l_axisX;
	sf::Joystick::Axis l_axisY;
	sf::Joystick::Axis r_axisX;
	sf::Joystick::Axis r_axisY;

	ButtonID(int Left, int Right, int Dash_left, int Dash_right, int Stance1, int Stance2, sf::Joystick::Axis LaX, sf::Joystick::Axis LaY, sf::Joystick::Axis RaX, sf::Joystick::Axis RaY)
	{
		left = Left;
		right = Right;
		dash_left = Dash_left;
		dash_right = Dash_right;
		stance1 = Stance1;
		stance2 = Stance2;
		l_axisX = LaX;
		l_axisY = LaY;
		r_axisX = RaX;
		r_axisY = RaY;
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

	ControllerState m_ControllerState;
	ButtonID m_ButtonID;
public:
	void SetBindings(int Left, int Right, int Dash_left, int Dash_right, int Stance1, int Stance2, sf::Joystick::Axis LaX, sf::Joystick::Axis LaY, sf::Joystick::Axis RaX, sf::Joystick::Axis RaY);
	void TakeInputs(int ControllerID);
	ControllerState ReadInputs();
	void Update();

	Input();
	~Input();
};

#endif