#ifndef _WEAPON_H
#define _WEAPON_H

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "GameObject.h"

#define SCALE 32.0f
#define DEFAULT_RADIUS 50.0f
#define DEFAULT_WEAPON_WIDTH 100.0f
#define DEFAULT_WEAPON_HEIGHT 10.0f
#define DEFAULT_DEBUG_RADIUS 4.0f

class Weapon : GameObject
{
private:
	bool flip;

	Vector2f m_ControlOffset;
	Vector2f m_AnchorOffset;
	Vector2f m_HitboxOffset;
	float m_FrontHandOffset;
	float m_BackHandOffset;

	Vector2f m_FrontHandPos;
	Vector2f m_BackHandPos;
	Vector2f m_ControlPos;
	Vector2f m_AnchorPos;
	
	CircleShape m_Circle;
	CircleShape m_ControlCircle;
	CircleShape m_AnchorCircle;
	CircleShape m_FrontHandCircle;
	CircleShape m_BackHandCircle;
	CircleShape m_HitCircle;

	RectangleShape m_WeaponRect;
public:
	CircleShape GetHitCircle() {return m_HitCircle;};
	void SetControlOffset(Vector2f ControlOffset) { m_ControlOffset = ControlOffset;};
	void SetControlRadius(float ControlRadius) { m_Circle.setRadius(ControlRadius); m_Circle.setOrigin(Vector2f(ControlRadius, ControlRadius)); };
	void SetAnchorOffset(Vector2f AnchorOffset) { m_AnchorOffset = AnchorOffset; };
	void SetHitboxOffset(Vector2f HitboxOffset) { m_HitboxOffset = HitboxOffset; };
	void SetHitboxRadius(float HitboxRadius) { m_HitCircle.setRadius(HitboxRadius); m_HitCircle.setOrigin(Vector2f(HitboxRadius, HitboxRadius)); };
	void SetWeaponSize(Vector2f WeaponSize) { m_WeaponRect.setSize(WeaponSize); m_WeaponRect.setOrigin(WeaponSize.x / 2, WeaponSize.y / 2); };
	void SetWeaponOrigin(Vector2f WeaponOrigin) { m_WeaponRect.setOrigin(WeaponOrigin); };

	Vector2f GetFrontHandPos() { return m_FrontHandPos; };
	Vector2f GetBackHandPos() { return m_BackHandPos; };

	Weapon();
	Weapon(float radius, Vector2f CirclePos, Vector2f ControlOffset, Vector2f AnchorPos, Vector2f AnchorOffset, Vector2f WeaponSize, Vector2f WeaponOrigin, Vector2f HitBoxOffset);
	~Weapon();

	b2Vec2 GetForce() { return b2Vec2(m_Body->GetLinearVelocity().x *  m_Body->GetMass(), m_Body->GetLinearVelocity().y *  m_Body->GetMass()); };

	void Update(Vector2f ControlPos, Vector2f CharPos, bool Flip, bool AllowFlip);
	void Draw(RenderWindow &Window, bool hitDebug);
};

#endif