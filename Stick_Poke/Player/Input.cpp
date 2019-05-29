#include "Input.h"

void Input::SetBindings(int Left, int Right, int Dash_left, int Dash_right, int Stance1, int Stance2, Joystick::Axis LaX, Joystick::Axis LaY, Joystick::Axis RaX, Joystick::Axis RaY)
{
	m_ButtonID = ButtonID(Left, Right, Dash_left, Dash_right, Stance1, Stance2, LaX, LaY, RaX, RaY);
}

void Input::TakeInputs(int ControllerID)
{
	if (m_Device == Devices::Controller)
	{
		m_ControllerState.left = Joystick::isButtonPressed(ControllerID, m_ButtonID.left);
		m_ControllerState.right = Joystick::isButtonPressed(ControllerID, m_ButtonID.right);
		m_ControllerState.dash_left = Joystick::isButtonPressed(ControllerID, m_ButtonID.dash_left);
		m_ControllerState.dash_right = Joystick::isButtonPressed(ControllerID, m_ButtonID.dash_right);
		m_ControllerState.stance1 = Joystick::isButtonPressed(ControllerID, m_ButtonID.stance1);
		m_ControllerState.stance2 = Joystick::isButtonPressed(ControllerID, m_ButtonID.stance2);
		m_ControllerState.lStick = Vector2f(Joystick::getAxisPosition(ControllerID, m_ButtonID.l_axisX), Joystick::getAxisPosition(ControllerID, m_ButtonID.l_axisY));
		m_ControllerState.rStick = Vector2f(Joystick::getAxisPosition(ControllerID, m_ButtonID.r_axisX), Joystick::getAxisPosition(ControllerID, m_ButtonID.r_axisY));
	}
	else if (m_Device == MouseKeyboard)
	{
		//m_ControllerState.left = Keyboard::isKeyPressed(Keyboard::A);
		//m_ControllerState.right = Keyboard::isKeyPressed(Keyboard::D);
		//m_ControllerState.dash_left = Keyboard::isKeyPressed(Keyboard::Q);
		//m_ControllerState.dash_right = Keyboard::isKeyPressed(Keyboard::E);
		//etc....
	}
}

ControllerState Input::ReadInputs()
{
	return m_ControllerState;
}

void Input::Update()
{
}

Input::Input()
{
}


Input::~Input()
{
}
