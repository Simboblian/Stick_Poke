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
	bool item1;
	bool item2;
	bool item3;
	bool item4;
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
		item1 = b;
		item2 = b;
		item3 = b;
		item4 = b;
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
	int item1;
	int item2;
	int item3;
	int item4;
	int stance1;
	int stance2;
	sf::Joystick::Axis lAxisX;
	sf::Joystick::Axis lAxisY;
	sf::Joystick::Axis rAxisX;
	sf::Joystick::Axis rAxisY;

	ButtonID(int Left, int Right, int Up, int Down, int Movement, int Item1, int Item2, int Item3, int Item4, int Stance1, int Stance2, sf::Joystick::Axis LX, sf::Joystick::Axis LY, sf::Joystick::Axis RX, sf::Joystick::Axis RY)
	{
		left = Left;
		right = Right;
		up = Up;
		down = Down;
		movement = Movement;
		item1 = Item1;
		item2 = Item2;
		item3 = Item3;
		item4 = Item4;
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
	Devices _device = MouseKeyboard;
	
	int _controllerID;

	sf::Vector2f _mousePos;

	ControlState *_inputBuffer[BUFFERSIZE];
	ControlState *_newState;
	ControlState _oldState;

	ButtonID _buttonID;

	short _frameIndex;

	sf::Vector2f MouseToJoystick(sf::RenderWindow &Window, sf::Vector2f CharacterPosition);
public:
	enum Control { c_Left, c_Right, c_Up, c_Down, c_Movement, c_Item1, c_Item2, c_Item3, c_Item4, c_Stance1, c_Stance2 };

	void SetBindings(int Left, int Right, int Up, int Down, int Movement, int Item1, int Item2, int Item3, int Item4, int Stance1, int Stance2, sf::Joystick::Axis LX, sf::Joystick::Axis LY, sf::Joystick::Axis RX, sf::Joystick::Axis RY);
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