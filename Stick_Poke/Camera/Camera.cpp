#include "Camera.h"

void Camera::Update(RenderWindow &Window)
{
	Vector2f size = m_View.getSize();

	m_View.setCenter(Vector2f(m_Position));

	Window.setView(m_View);
}

Camera::Camera(Vector2f Size)
{
	m_Size = Size;
	m_Position = Vector2f(0, 0);
	m_View.reset(FloatRect(0, 0, m_Size.x, m_Size.y));
	m_View.setCenter(Vector2f(m_Position));
}

Camera::Camera()
{
}

Camera::~Camera()
{
}
