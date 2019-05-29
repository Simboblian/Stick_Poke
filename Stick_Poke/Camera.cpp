#include "Camera.h"

void Camera::Update(sf::RenderWindow &Window)
{
	sf::Vector2f size = m_View.getSize();

	m_View.setCenter(sf::Vector2f(m_Position));

	Window.setView(m_View);
}

Camera::Camera(sf::Vector2f Size)
{
	m_Size = Size;
	m_Position = sf::Vector2f(0, 0);
	m_View.reset(sf::FloatRect(0, 0, m_Size.x, m_Size.y));
	m_View.setCenter(sf::Vector2f(m_Position));
}

Camera::Camera()
{
}

Camera::~Camera()
{
}
