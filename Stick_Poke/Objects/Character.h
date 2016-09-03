#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"

class Character : GameObject
{
private:
	RectangleShape m_Rect;
	Vector2f m_Velocity;
public:
	void Draw(RenderWindow &Window);
	void Update();
	Vector2f GetPosition() { return m_Position; };

	Character(b2World & World);

	Character();
	~Character();
};

#endif
