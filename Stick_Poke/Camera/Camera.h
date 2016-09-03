#ifndef _CAMERA_H
#define _CAMERA_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Camera
{
private:
	Vector2f m_Position, m_Size;
	
	View m_View;
	RectangleShape m_ViewWindow;
public:
	View GetCamera() { return m_View; };
	Vector2f GetStartPoint() { return sf::Vector2f(m_View.getCenter().x - m_View.getSize().x / 2, m_View.getCenter().y - m_View.getSize().y / 2); };
	RectangleShape GetViewWindow() { return m_ViewWindow; };
	void SetZoom(float zoom) { m_View.zoom(zoom); };

	void ApplyVector(Vector2f Vector) { m_Position += Vector; };
	void SetPosition(Vector2f Position) { m_Position = Position; };
	
	void Update(RenderWindow & Window);

	Camera(Vector2f Size);
	Camera();
	~Camera();
};

#endif