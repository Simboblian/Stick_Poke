#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

using namespace sf;

struct ControllerState
{
	bool left;
	bool right;
	bool dash_left;
	bool dash_right;
	bool stance1;
	bool stance2;
	Vector2f lStick;
	Vector2f rStick;

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
	Joystick::Axis l_axisX;
	Joystick::Axis l_axisY;
	Joystick::Axis r_axisX;
	Joystick::Axis r_axisY;

	ButtonID(int Left, int Right, int Dash_left, int Dash_right, int Stance1, int Stance2, Joystick::Axis LaX, Joystick::Axis LaY, Joystick::Axis RaX, Joystick::Axis RaY)
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
	void SetBindings(int Left, int Right, int Dash_left, int Dash_right, int Stance1, int Stance2, Joystick::Axis LaX, Joystick::Axis LaY, Joystick::Axis RaX, Joystick::Axis RaY);
	void TakeInputs(int ControllerID);
	ControllerState ReadInputs();
	void Update();

	Input();
	~Input();
};

#endif