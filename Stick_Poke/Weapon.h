#ifndef _WEAPON_H
#define _WEAPON_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

#define DEFAULT_RADIUS 50.0f
#define DEFAULT_WEAPON_WIDTH 100.0f
#define DEFAULT_WEAPON_HEIGHT 10.0f
#define DEFAULT_DEBUG_RADIUS 5.0f

class Weapon : GameObject
{
private:
	bool flip;

	b2Body *m_HitSensor;

	sf::Vector2f m_ControlOffset;
	sf::Vector2f m_AnchorOffset;
	sf::Vector2f m_HitboxOffset;
	float m_FrontHandOffset;
	float m_BackHandOffset;

	sf::Vector2f m_FrontHandPos;
	sf::Vector2f m_BackHandPos;
	sf::Vector2f m_ControlPos;
	sf::Vector2f m_AnchorPos;

	sf::Vector2f m_ControlPosOffset;
	
	sf::CircleShape m_Circle;
	sf::CircleShape m_ControlCircle;
	sf::CircleShape m_AnchorCircle;
	sf::CircleShape m_FrontHandCircle;
	sf::CircleShape m_BackHandCircle;
	sf::CircleShape m_HitCircle;

	sf::RectangleShape m_WeaponRect;

public:
	sf::CircleShape GetHitCircle() {return m_HitCircle;};

	void SetControlOffset(sf::Vector2f ControlOffset) { m_ControlOffset = ControlOffset;};
	void SetControlRadius(float ControlRadius) { m_Circle.setRadius(ControlRadius); m_Circle.setOrigin(sf::Vector2f(ControlRadius, ControlRadius)); };
	void SetAnchorOffset(sf::Vector2f AnchorOffset) { m_AnchorOffset = AnchorOffset; };
	void SetHitboxOffset(sf::Vector2f HitboxOffset) { m_HitboxOffset = HitboxOffset; };
	void SetHitboxRadius(float HitboxRadius) { m_HitCircle.setRadius(HitboxRadius); m_HitCircle.setOrigin(sf::Vector2f(HitboxRadius, HitboxRadius)); };
	void SetWeaponSize(sf::Vector2f WeaponSize) { m_WeaponRect.setSize(WeaponSize); m_WeaponRect.setOrigin(WeaponSize.x / 2, WeaponSize.y / 2); };
	void SetWeaponOrigin(sf::Vector2f WeaponOrigin) { m_WeaponRect.setOrigin(WeaponOrigin); };
	void SetFrontHandOffset(float FrontHandOffset) { m_FrontHandOffset = FrontHandOffset; };
	void SetBackHandOffset(float BackHandOffset) { m_BackHandOffset = BackHandOffset; };


	sf::Vector2f GetFrontHandPos() { return m_FrontHandPos; };
	sf::Vector2f GetBackHandPos() { return m_BackHandPos; };
	sf::Vector2f GetWeaponOffset() { return m_ControlPos; };

	Weapon();
	Weapon(b2World &World);
	Weapon(b2World &World, float radius, sf::Vector2f CirclePos, sf::Vector2f ControlOffset, sf::Vector2f AnchorPos, sf::Vector2f AnchorOffset, sf::Vector2f WeaponSize, sf::Vector2f WeaponOrigin, sf::Vector2f HitBoxOffset);
	~Weapon();

	//b2Vec2 GetForce() { return b2Vec2(m_Body->GetLinearVelocity().x *  m_Body->GetMass(), m_Body->GetLinearVelocity().y *  m_Body->GetMass()); };

	void Update(sf::Vector2f ControlPos, sf::Vector2f CharPos, sf::Vector2f CharSize, bool Flip, bool AllowFlip);
	void Draw(sf::RenderWindow &Window, bool hitDebug);
};

#endif