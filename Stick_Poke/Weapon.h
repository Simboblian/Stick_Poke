#ifndef _WEAPON_H
#define _WEAPON_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <stdlib.h>

#define DEFAULT_RADIUS 50.0f
#define DEFAULT_WEAPON_WIDTH 100.0f
#define DEFAULT_WEAPON_HEIGHT 10.0f
#define DEFAULT_DEBUG_RADIUS 5.0f

enum Grip { G_TWOHAND, G_FRONTHAND, G_BACKHAND};

class Weapon : public GameObject
{
private:
	bool m_Flip;
	Grip m_Grip = G_TWOHAND;

	float m_TopSpeed = 100;
	float m_CurrentSpeed = 100;

	sf::Vector2f m_ControlOffset;
	sf::Vector2f m_TargetOffset;
	sf::Vector2f m_AnchorOffset;
	sf::Vector2f m_HitboxOffset;
	float m_FrontHandOffset;
	float m_BackHandOffset;

	sf::Vector2f m_FrontHandPos;
	sf::Vector2f m_BackHandPos;
	sf::Vector2f m_TargetPos;
	sf::Vector2f m_ControlPos;
	sf::Vector2f m_AnchorPos;

	sf::Vector2f m_OldCharPos;
	sf::Vector2f m_OldHitboxPos;
	
	sf::CircleShape m_Circle;
	sf::CircleShape m_ControlCircle;
	sf::CircleShape m_TargetCircle;
	sf::CircleShape m_AnchorCircle;
	sf::CircleShape m_FrontHandCircle;
	sf::CircleShape m_BackHandCircle;
	sf::CircleShape m_HitCircle;

	sf::RectangleShape m_WeaponRect;

	sf::Vector2f Seek(sf::Vector2f Target, sf::Vector2f Current);
public:
	void SetTargetOffset(sf::Vector2f TargetOffset) { m_TargetOffset = TargetOffset;};
	void SetAnchorOffset(sf::Vector2f AnchorOffset) { m_AnchorOffset = AnchorOffset; };
	void SetHitboxOffset(sf::Vector2f HitboxOffset) { m_HitboxOffset = HitboxOffset; };
	void SetWeaponSize(sf::Vector2f WeaponSize) { m_WeaponRect.setSize(WeaponSize); m_WeaponRect.setOrigin(WeaponSize.x / 2, WeaponSize.y / 2); };
	void SetWeaponOrigin(sf::Vector2f WeaponOrigin) { m_WeaponRect.setOrigin(WeaponOrigin); };
	void SetControlRadius(float ControlRadius) { m_Circle.setRadius(ControlRadius); m_Circle.setOrigin(sf::Vector2f(ControlRadius, ControlRadius)); };
	void SetHitboxRadius(float HitboxRadius) { m_HitCircle.setRadius(HitboxRadius); m_HitCircle.setOrigin(sf::Vector2f(HitboxRadius, HitboxRadius)); };
	void SetFrontHandOffset(float FrontHandOffset) { m_FrontHandOffset = FrontHandOffset; };
	void SetBackHandOffset(float BackHandOffset) { m_BackHandOffset = BackHandOffset; };
	void SetTopSpeed(float Speed) { m_TopSpeed = Speed; };
	void SetSpeed(float Speed) { m_CurrentSpeed = Speed; };
	void SetGrip(Grip NewGrip) { m_Grip = NewGrip; };

	void ResetSpeed() { m_CurrentSpeed = m_TopSpeed; };

	sf::Vector2f GetHitVector();
	sf::Vector2f GetFrontHandPos() { return m_Flip ? m_BackHandPos : m_FrontHandPos; };
	sf::Vector2f GetBackHandPos() { return m_Flip ? m_FrontHandPos : m_BackHandPos; };
	sf::Vector2f GetHitboxOffset() { return m_HitboxOffset; };
	sf::RectangleShape GetWeaponRect() { return m_WeaponRect; };
	sf::CircleShape GetControlCircle() { return m_ControlCircle; };
	sf::CircleShape GetTargetCircle() { return m_TargetCircle; };
	sf::CircleShape GetAnchorCircle() { return m_AnchorCircle; };
	sf::CircleShape GetFrontHandCircle() { return m_FrontHandCircle; };
	sf::CircleShape GetBackHandCircle() { return m_BackHandCircle; };
	sf::CircleShape GetCircle() { return m_Circle; };
	sf::CircleShape GetHitCircle() { return m_HitCircle; };
	float GetFrontHandOffset() { return m_FrontHandOffset; };
	float GetBackHandOffset() { return m_BackHandOffset; };
	float GetTopSpeed() { return m_TopSpeed; };
	sf::Vector2f GetWeaponOffset() { return m_ControlPos; };
	Grip GetGrip() { return m_Grip; };

	Weapon();
	Weapon(Weapon *NewWeapon);
	Weapon(b2World &World);
	Weapon(b2World &World, float radius, sf::Vector2f CirclePos, sf::Vector2f ControlOffset, sf::Vector2f AnchorPos, sf::Vector2f AnchorOffset, sf::Vector2f WeaponSize, sf::Vector2f WeaponOrigin, sf::Vector2f HitBoxOffset);
	~Weapon();

	//b2Vec2 GetForce() { return b2Vec2(m_Body->GetLinearVelocity().x *  m_Body->GetMass(), m_Body->GetLinearVelocity().y *  m_Body->GetMass()); };

	void Update(sf::Vector2f ControlPos, sf::Vector2f CharPos, sf::Vector2f CharSize, bool Flip, bool AllowFlip);
	void Draw(sf::RenderWindow &Window, bool hitDebug);
};

#endif