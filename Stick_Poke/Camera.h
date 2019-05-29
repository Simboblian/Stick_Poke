#ifndef _CAMERA_H
#define _CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::Vector2f m_Position, m_Size;
	
	sf::View m_View;
	sf::RectangleShape m_ViewWindow;
public:
	sf::View GetCamera() { return m_View; };
	sf::Vector2f GetStartPoint() { return sf::Vector2f(m_View.getCenter().x - m_View.getSize().x / 2, m_View.getCenter().y - m_View.getSize().y / 2); };
	sf::RectangleShape GetViewWindow() { return m_ViewWindow; };
	void SetZoom(float zoom) { m_View.zoom(zoom); };

	void ApplyVector(sf::Vector2f Vector) { m_Position += Vector; };
	void SetPosition(sf::Vector2f Position) { m_Position = Position; };
	
	void Update(sf::RenderWindow & Window);

	Camera(sf::Vector2f Size);
	Camera();
	~Camera();
};

#endif