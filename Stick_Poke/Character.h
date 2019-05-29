#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"
#include "Input.h"
#include "Weapon.h"

class Character : public GameObject
{
private:
	sf::RectangleShape m_Rect;
	sf::RectangleShape m_BackBicep;
	sf::RectangleShape m_BackForearm;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_OldMousePos;
	sf::Vector2f m_MousePos;

	Weapon* m_Weapon;
public:
	void Draw(sf::RenderWindow &Window);
	void Update(sf::Vector2f Gravity);
	sf::Vector2f GetPosition() { return m_Position; };
	void SetPosition(sf::Vector2f Position) { m_Position = Position; };
	void SetState(state State) { m_State = State; };
	sf::RectangleShape GetShape() { return m_Rect; };
	void SetInputDevice(ControllerState State);

	Character();
	~Character();
};

#endif
