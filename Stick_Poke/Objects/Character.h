#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"
#include "Player/Input.h"
#include "Weapon.h"

class Character : GameObject
{
private:
	enum state {HIT, STANDING};
	state m_State;

	RectangleShape m_Rect;
	RectangleShape m_BackBicep;
	RectangleShape m_BackForearm;
	Vector2f m_Velocity;
	Vector2f m_OldMousePos;
	Vector2f m_MousePos;

	Weapon* m_Weapon;
public:
	void Draw(RenderWindow &Window);
	void Update();
	Vector2f GetPosition() { return m_Position; };
	void SetPosition(Vector2f Position) { m_Body->SetTransform(SFVECtoB2VEC(Position, true), 0); };
	void SetInputDevice(ControllerState State);

	Character(b2World & World);

	Character();
	~Character();
};

#endif
