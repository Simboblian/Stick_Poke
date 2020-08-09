#include "Input.h"

sf::Vector2f Input::MouseToJoystick(sf::RenderWindow & Window, sf::Vector2f CharacterPosition)
{
	sf::Vector2f result = Window.mapPixelToCoords(sf::Vector2i((sf::Mouse::getPosition().x - Window.getPosition().x) - floorf(CharacterPosition.x), (sf::Mouse::getPosition().y - Window.getPosition().y) - floorf(CharacterPosition.y)));

	result = Utility::Truncate(result, 100);

	return result;
}

void Input::SetBindings(int Left, int Right, int Up, int Down, int Movement, int Item1, int Item2, int Item3, int Item4, int Stance1, int Stance2, sf::Joystick::Axis LX, sf::Joystick::Axis LY, sf::Joystick::Axis RX, sf::Joystick::Axis RY)
{
	_buttonID = ButtonID(Left, Right, Up, Down, Movement, Item1, Item2, Item3, Item4, Stance1, Stance2, LX, LY, RX, RY);
}

void Input::TakeInputs(sf::RenderWindow &Window, sf::Vector2f CharacterPosition, int ControllerID)
{
	_newState = new ControlState(false);

	if (_device == Devices::Controller)
	{
		_newState->left = sf::Joystick::isButtonPressed(ControllerID, _buttonID.left);
		_newState->right = sf::Joystick::isButtonPressed(ControllerID, _buttonID.right);
		_newState->up = sf::Joystick::isButtonPressed(ControllerID, _buttonID.up);
		_newState->down = sf::Joystick::isButtonPressed(ControllerID, _buttonID.down);
		_newState->movement = sf::Joystick::isButtonPressed(ControllerID, _buttonID.movement);
		_newState->item1 = sf::Joystick::isButtonPressed(ControllerID, _buttonID.item1);
		_newState->item2 = sf::Joystick::isButtonPressed(ControllerID, _buttonID.item2);
		_newState->item3 = sf::Joystick::isButtonPressed(ControllerID, _buttonID.item3);
		_newState->item4 = sf::Joystick::isButtonPressed(ControllerID, _buttonID.item4);
		_newState->stance1 = sf::Joystick::isButtonPressed(ControllerID, _buttonID.stance1);
		_newState->stance2 = sf::Joystick::isButtonPressed(ControllerID, _buttonID.stance2);
		_newState->lStick = sf::Vector2f(sf::Joystick::getAxisPosition(ControllerID, _buttonID.lAxisX), sf::Joystick::getAxisPosition(ControllerID, _buttonID.lAxisY));
		_newState->rStick = sf::Vector2f(sf::Joystick::getAxisPosition(ControllerID, _buttonID.rAxisX), sf::Joystick::getAxisPosition(ControllerID, _buttonID.rAxisY));
	}
	else if (_device == MouseKeyboard)
	{
		_newState->rStick = MouseToJoystick(Window, CharacterPosition);

		_newState->left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		_newState->right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		_newState->up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		_newState->down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		_newState->movement = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		_newState->item1 = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
		_newState->item2 = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		_newState->item3 = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		_newState->item4 = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
		_newState->stance1 = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		_newState->stance2 = sf::Mouse::isButtonPressed(sf::Mouse::Right);
		
		//etc...
	}
}

void Input::Update(sf::RenderWindow &Window, sf::Vector2f CharacterPosition, sf::Vector2f CameraPosition)
{
	if (_device == MouseKeyboard)
		sf::Mouse::setPosition(sf::Vector2i(Window.getPosition().x + (Window.getSize().x / 2) + _newState->rStick.x, Window.getPosition().y + (Window.getSize().y / 2) + _newState->rStick.y));

	_inputBuffer[_frameIndex] = _newState;

	if (++_frameIndex >= BUFFERSIZE)
		_frameIndex = 0;
}

ControlState * Input::GetInputBuffer()
{
	bool returnValue = false;
	int i = _frameIndex;
	_frameIndex - 1 < 0 ? i = BUFFERSIZE - 1 : i -= 1;
	return _inputBuffer[i];
}

bool Input::WasInputDownAtFrame(Control input, int numberOfFramesAgo)
{
	bool returnValue = false;
	int i = _frameIndex;
	_frameIndex - numberOfFramesAgo < 0 ? i = BUFFERSIZE - 1 : i -= numberOfFramesAgo;
	ControlState* currentState = _inputBuffer[i];
	
	switch (input)
	{
	case Control::c_Left:
		if (currentState->left)
			returnValue = true;
		break;
	case Control::c_Right:
		if (currentState->right)
			returnValue = true;
		break;
	case Control::c_Down:
		if (currentState->down)
			returnValue = true;
		break;
	case Control::c_Up:
		if (currentState->up)
			returnValue = true;
		break;
	case Control::c_Movement:
		if (currentState->movement)
			returnValue = true;
		break;
	case Control::c_Stance1:
		if (currentState->stance1)
			returnValue = true;
		break;
	case Control::c_Stance2:
		if (currentState->stance2)
			returnValue = true;
		break;
	default:
		break;
	}

	return returnValue;
}

bool Input::WasInputPressedAtFrame(Control input, int numberOfFramesAgo)
{
	return(WasInputDownAtFrame(input, numberOfFramesAgo) && !WasInputDownAtFrame(input, numberOfFramesAgo + 1));
}

bool Input::WasInputReleasedAtFrame(Control input, int numberOfFramesAgo)
{
	return(!WasInputDownAtFrame(input, numberOfFramesAgo) && WasInputDownAtFrame(input, numberOfFramesAgo + 1));
}

bool Input::WasInputHeldForFrames(Control input, int numberOfFramesAgo, int frameDuration)
{
	bool returnValue = true;

	for (int i = 0; i < frameDuration; i++)
	{
		if (!WasInputDownAtFrame(input, numberOfFramesAgo + i))
			returnValue = false;
	}
	return returnValue;
}

Input::Input()
{
	_newState = new ControlState(false);

	for (int i = 0; i < BUFFERSIZE; i++)
		_inputBuffer[i] = new ControlState(false);

	_frameIndex = 0;
}


Input::~Input()
{
}
