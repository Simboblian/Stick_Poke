#ifndef _WEAPON_H
#define _WEAPON_H

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "GameObject.h"

#define SCALE 32.0f

class Weapon : GameObject
{
private:
	bool flip;
	float hitBoxOffset;

	Vector2f m_ControlOffset;
	Vector2f m_AnchorOffset;
	Vector2f m_ControlPos;
	Vector2f m_AnchorPos;
	
	CircleShape m_Circle;
	CircleShape m_ControlCircle;
	CircleShape m_AnchorCircle;
	CircleShape m_HitCircle;
	
	b2Body *chainBody1;
	b2Body *chainBody2;
	b2Body *chainBody3;
	b2Body *chainBody4;
	b2Body *chainBody5;
	b2Body *m_CircleBody;

	b2Body *m_ControlBody;
	b2Body *m_AnchorBody;

	RectangleShape m_WeaponRect;
public:
	CircleShape GetHitCircle() {return m_HitCircle;};

	Weapon(float radius, Vector2f CirclePos, Vector2f ControlOffset, Vector2f AnchorPos, Vector2f AnchorOffset, Vector2f WeaponSize, Vector2f WeaponOrigin, float HitBoxOffset);
	~Weapon();
	
	void AddPhysics(b2World& World, int index);
	void AddChainLink(b2World& World, b2Body& PrevBody);
	void OldAddPhysics(b2World& World, int index);
	b2Vec2 GetForce() { return b2Vec2(m_Body->GetLinearVelocity().x *  m_Body->GetMass(), m_Body->GetLinearVelocity().y *  m_Body->GetMass()); };

	void Update(Vector2f ControlPos, Vector2f CharPos, bool Flip, bool AllowFlip);
	void Draw(RenderWindow &Window, bool hitDebug);
};

#endif