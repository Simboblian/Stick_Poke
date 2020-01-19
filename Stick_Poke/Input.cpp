#include "Input.h"

sf::Vector2f Input::MouseToJoystick(sf::RenderWindow & Window, sf::Vector2f CharacterPosition)
{
	sf::Vector2f result = Window.mapPixelToCoords(sf::Vector2i((sf::Mouse::getPosition().x - Window.getPosition().x) - floorf(CharacterPosition.x), (sf::Mouse::getPosition().y - Window.getPosition().y) - floorf(CharacterPosition.y)));

	result = Utility::Truncate(result, 100);

	return result;
}

void Input::SetBindings(int Left, int Right, int Up, int Down, int Movement, int Item1, int Item2, int Item3, int Item4, int Stance1, int Stance2, sf::Joystick::Axis LX, sf::Joystick::Axis LY, sf::Joystick::Axis RX, sf::Joystick::Axis RY)
{
	m_ButtonID = ButtonID(Left, Right, Up, Down, Movement, Item1, Item2, Item3, Item4, Stance1, Stance2, LX, LY, RX, RY);
}

void Input::TakeInputs(sf::RenderWindow &Window, sf::Vector2f CharacterPosition, int ControllerID)
{
	m_NewState = new ControlState(false);

	if (m_Device == Devices::Controller)
	{
		m_NewState->left = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.left);
		m_NewState->right = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.right);
		m_NewState->up = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.up);
		m_NewState->down = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.down);
		m_NewState->movement = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.movement);
		m_NewState->item1 = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.item1);
		m_NewState->item2 = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.item2);
		m_NewState->item3 = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.item3);
		m_NewState->item4 = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.item4);
		m_NewState->stance1 = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.stance1);
		m_NewState->stance2 = sf::Joystick::isButtonPressed(ControllerID, m_ButtonID.stance2);
		m_NewState->lStick = sf::Vector2f(sf::Joystick::getAxisPosition(ControllerID, m_ButtonID.lAxisX), sf::Joystick::getAxisPosition(ControllerID, m_ButtonID.lAxisY));
		m_NewState->rStick = sf::Vector2f(sf::Joystick::getAxisPosition(ControllerID, m_ButtonID.rAxisX), sf::Joystick::getAxisPosition(ControllerID, m_ButtonID.rAxisY));
	}
	else if (m_Device == MouseKeyboard)
	{
		m_NewState->rStick = MouseToJoystick(Window, CharacterPosition);

		m_NewState->left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		m_NewState->right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		m_NewState->up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		m_NewState->down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		m_NewState->movement = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		m_NewState->item1 = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
		m_NewState->item2 = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		m_NewState->item3 = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		m_NewState->item4 = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
		m_NewState->stance1 = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		m_NewState->stance2 = sf::Mouse::isButtonPressed(sf::Mouse::Right);
		
		//etc...
	}
}

void Input::Update(sf::RenderWindow &Window, sf::Vector2f CharacterPosition, sf::Vector2f CameraPosition)
{
	if (m_Device == MouseKeyboard)
		sf::Mouse::setPosition(sf::Vector2i(Window.getPosition().x + (Window.getSize().x / 2) + m_NewState->rStick.x, Window.getPosition().y + (Window.getSize().y / 2) + m_NewState->rStick.y));

	m_InputBuffer[m_FrameIndex] = m_NewState;

	if (++m_FrameIndex >= BUFFERSIZE)
		m_FrameIndex = 0;
}

ControlState * Input::GetInputBuffer()
{
	bool returnValue = false;
	int i = m_FrameIndex;
	m_FrameIndex - 1 < 0 ? i = BUFFERSIZE - 1 : i -= 1;
	return m_InputBuffer[i];
}

bool Input::WasInputDownAtFrame(Control input, int numberOfFramesAgo)
{
	bool returnValue = false;
	int i = m_FrameIndex;
	m_FrameIndex - numberOfFramesAgo < 0 ? i = BUFFERSIZE - 1 : i -= numberOfFramesAgo;
	ControlState* currentState = m_InputBuffer[i];
	
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
	m_NewState = new ControlState(false);

	for (int i = 0; i < BUFFERSIZE; i++)
		m_InputBuffer[i] = new ControlState(false);

	m_FrameIndex = 0;
}


Input::~Input()
{
}
