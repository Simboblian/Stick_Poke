#ifndef _INPUT_H
#define _INPUT_H

#include <SFML/Graphics.hpp>
#include "Utility.h"

#define BUFFERSIZE 120

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

	ControlState(bool b)
	{
		left = b;
		right = b;
		up = b;
		down = b;
		movement = b;
		stance1 = b;
		stance2 = b;
	};

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
	Devices m_Device = MouseKeyboard;
	
	int m_ControllerID;

	sf::Vector2f m_MousePos;
	sf::Vector2i moPos;
	sf::Vector2i freshMoPos;

	ControlState *m_InputBuffer[BUFFERSIZE];
	ControlState *m_NewState;
	ControlState m_OldState;

	ButtonID m_ButtonID;

	short m_FrameIndex;

	sf::Vector2f MouseToJoystick(sf::RenderWindow &Window, sf::Vector2f CharacterPosition);
public:
	enum Control { c_Left, c_Right, c_Up, c_Down, c_Movement, c_Stance1, c_Stance2 };

	void SetBindings(int Left, int Right, int Up, int Down, int Movement, int Stance1, int Stance2, sf::Joystick::Axis LX, sf::Joystick::Axis LY, sf::Joystick::Axis RX, sf::Joystick::Axis RY);
	void TakeInputs(sf::RenderWindow & Window, sf::Vector2f CharacterPosition, int ControllerID);
	void Update(sf::RenderWindow &Window, sf::Vector2f CharacterPosition, sf::Vector2f CameraPosition);

	ControlState* GetInputBuffer();

	bool WasInputDownAtFrame(Control input, int numberOfFramesAgo);
	bool WasInputHeldForFrames(Control input, int numberOfFramesAgo, int FrameDuration);
	bool WasInputPressedAtFrame(Control input, int numberOfFramesAgo);
	bool WasInputReleasedAtFrame(Control input, int numberOfFramesAgo);

	Input();
	~Input();
};

#endif