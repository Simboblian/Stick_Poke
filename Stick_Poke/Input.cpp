#include "Input.h"

sf::Vector2f Input::MouseToJoystick(sf::RenderWindow & Window, sf::Vector2f ViewPosition)
{
	sf::Vector2f result = Window.mapPixelToCoords(sf::Vector2i((sf::Mouse::getPosition().x - Window.getPosition().x) - ViewPosition.x, (sf::Mouse::getPosition().y - Window.getPosition().y) - ViewPosition.y));

	result = Utility::Truncate(result, 100);

	return result;
}

void Input::SetBindings(int Left, int Right, int Up, int Down, int Movement, int Stance1, int Stance2, sf::Joystick::Axis LX, sf::Joystick::Axis LY, sf::Joystick::Axis RX, sf::Joystick::Axis RY)
{
	m_ButtonID = ButtonID(Left, Right, Up, Down, Movement, Stance1, Stance2, LX, LY, RX, RY);
}

void Input::TakeInputs(sf::RenderWindow &Window, sf::Vector2f CameraPosition, int ControllerID)
{
	if (m_Device == Devices::Controller)
	{
		m_InputState.left = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.left);
		m_InputState.right = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.right);
		m_InputState.movement = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.movement);
		m_InputState.stance1 = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.stance1);
		m_InputState.stance2 = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.stance2);
		m_InputState.lStick = sf::Vector2f(sf::Joystick::getAxisPosition(ControllerID, m_ButtonID.lAxisX), sf::Joystick::getAxisPosition(ControllerID, m_ButtonID.lAxisY));
		m_InputState.rStick = sf::Vector2f(sf::Joystick::getAxisPosition(ControllerID, m_ButtonID.rAxisX), sf::Joystick::getAxisPosition(ControllerID, m_ButtonID.rAxisY));
	}
	else if (m_Device == MouseKeyboard)
	{
		m_InputState.rStick = MouseToJoystick(Window, CameraPosition);

		m_InputState.left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		m_InputState.right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		m_InputState.up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		m_InputState.down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		m_InputState.movement = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		
		//etc...
	}
}

ControlState Input::ReadInputs()
{
	return m_InputState;
}

void Input::Update(sf::RenderWindow &Window)
{
	if(m_Device == MouseKeyboard)
		sf::Mouse::setPosition(sf::Vector2i(Window.getPosition().x + (Window.getSize().x /2), Window.getPosition().y + (Window.getSize().y / 2)));
}

Input::Input()
{
}


Input::~Input()
{
}
