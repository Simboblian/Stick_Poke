#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"
#include <iostream>
#include <stdlib.h>
#include "Input.h"
#include "Weapon.h"

#define ARMSECTIONLENGTH 40

class Character : public GameObject
{
private:
	sf::RectangleShape m_Rect;

	sf::RectangleShape m_BackBicep;
	sf::CircleShape m_BackElbowCircle;
	sf::RectangleShape m_BackForearm;

	sf::RectangleShape m_FrontBicep;
	sf::CircleShape m_FrontElbowCircle;
	sf::RectangleShape m_FrontForearm;


	sf::VertexArray m_BackArm;
	sf::VertexArray m_FrontArm;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_WeaponPos;
	sf::Vector2f m_BackShoulder;
	sf::Vector2f m_BackElbow;
	sf::Vector2f m_FrontShoulder;
	sf::Vector2f m_FrontElbow;



	float deg = 90;

	Weapon* m_Weapon;
	sf::Vector2f CalculateElbow(sf::Vector2f Shoulder, sf::Vector2f Wrist);
	void UpdateArmPositions();
public:
	void Draw(sf::RenderWindow &Window);
	void Update(sf::Vector2f Gravity);

	void SetState(state State) { m_State = State; };
	sf::RectangleShape GetShape() { return m_Rect; };
	sf::Vector2f GetWeaponStuff() { return m_Weapon->GetStuff(); };
	void ReceiveInputs(ControlState State);

	Character(b2World &World);
	Character();
	~Character();
};

#endif
