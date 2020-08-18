#ifndef _WEAPON_H
#define _WEAPON_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

#define DEFAULT_RADIUS 50.0f
#define DEFAULT_WEAPON_WIDTH 100.0f
#define DEFAULT_WEAPON_HEIGHT 10.0f
#define DEFAULT_DEBUG_RADIUS 5.0f

enum Grip { G_TWOHAND, G_FRONTHAND, G_BACKHAND};

class Weapon : public GameObject
{
private:
	bool _flip;
	Grip _grip = G_TWOHAND;

	float _topSpeed = 100;
	float _currentSpeed = 100;

	sf::Vector2f _controlOffset;
	sf::Vector2f _targetOffset;
	sf::Vector2f _anchorOffset;
	sf::Vector2f _hitboxOffset;
	float _frontHandOffset;
	float _backHandOffset;

	sf::Vector2f _frontHandPos;
	sf::Vector2f _backHandPos;
	sf::Vector2f _targetPos;
	sf::Vector2f _controlPos;
	sf::Vector2f _anchorPos;

	sf::Vector2f _oldCharPos;
	sf::Vector2f _oldHitboxPos;
	
	sf::CircleShape _circle;
	sf::CircleShape _controlCircle;
	sf::CircleShape _targetCircle;
	sf::CircleShape _anchorCircle;
	sf::CircleShape _frontHandCircle;
	sf::CircleShape _backHandCircle;
	sf::CircleShape _hitCircle;

	sf::RectangleShape _weaponRect;

	sf::Vector2f Seek(sf::Vector2f Target, sf::Vector2f Current);
public:
	void SetTargetOffset(sf::Vector2f TargetOffset) { _targetOffset = TargetOffset;};
	void SetAnchorOffset(sf::Vector2f AnchorOffset) { _anchorOffset = AnchorOffset; };
	void SetHitboxOffset(sf::Vector2f HitboxOffset) { _hitboxOffset = HitboxOffset; };
	void SetWeaponSize(sf::Vector2f WeaponSize) { _weaponRect.setSize(WeaponSize); _weaponRect.setOrigin(WeaponSize.x / 2, WeaponSize.y / 2); };
	void SetWeaponOrigin(sf::Vector2f WeaponOrigin) { _weaponRect.setOrigin(WeaponOrigin); };
	void SetControlRadius(float ControlRadius) { _circle.setRadius(ControlRadius); _circle.setOrigin(sf::Vector2f(ControlRadius, ControlRadius)); };
	void SetHitboxRadius(float HitboxRadius) { _hitCircle.setRadius(HitboxRadius); _hitCircle.setOrigin(sf::Vector2f(HitboxRadius, HitboxRadius)); };
	void SetFrontHandOffset(float FrontHandOffset) { _frontHandOffset = FrontHandOffset; };
	void SetBackHandOffset(float BackHandOffset) { _backHandOffset = BackHandOffset; };
	void SetTopSpeed(float Speed) { _topSpeed = Speed; };
	void SetSpeed(float Speed) { _currentSpeed = Speed; };
	void SetGrip(Grip NewGrip) { _grip = NewGrip; };

	void ResetSpeed() { _currentSpeed = _topSpeed; };

	sf::Vector2f GetHitVector();
	sf::Vector2f GetFrontHandPos() { return _flip ? _backHandPos : _frontHandPos; };
	sf::Vector2f GetBackHandPos() { return _flip ? _frontHandPos : _backHandPos; };
	sf::Vector2f GetHitboxOffset() { return _hitboxOffset; };
	sf::RectangleShape GetWeaponRect() { return _weaponRect; };
	sf::CircleShape GetControlCircle() { return _controlCircle; };
	sf::CircleShape GetTargetCircle() { return _targetCircle; };
	sf::CircleShape GetAnchorCircle() { return _anchorCircle; };
	sf::CircleShape GetFrontHandCircle() { return _frontHandCircle; };
	sf::CircleShape GetBackHandCircle() { return _backHandCircle; };
	sf::CircleShape GetCircle() { return _circle; };
	sf::CircleShape GetHitCircle() { return _hitCircle; };
	float GetFrontHandOffset() { return _frontHandOffset; };
	float GetBackHandOffset() { return _backHandOffset; };
	float GetTopSpeed() { return _topSpeed; };
	sf::Vector2f GetWeaponOffset() { return _controlPos; };
	Grip GetGrip() { return _grip; };

	Weapon();
	Weapon(Weapon *NewWeapon);
	Weapon(b2World &World);
	Weapon(b2World &World, float radius, sf::Vector2f CirclePos, sf::Vector2f ControlOffset, sf::Vector2f AnchorPos, sf::Vector2f AnchorOffset, sf::Vector2f WeaponSize, sf::Vector2f WeaponOrigin, sf::Vector2f HitBoxOffset);
	~Weapon();

	//b2Vec2 GetForce() { return b2Vec2(m_Body->GetLinearVelocity().x *  m_Body->GetMass(), m_Body->GetLinearVelocity().y *  m_Body->GetMass()); };

	void Update(sf::Vector2f ControlPos, sf::Vector2f CharPos, sf::Vector2f CharSize, bool Flip, bool AllowFlip);
	void UpdateHandPosition(Grip CURRENTGRIP);

	void Draw(sf::RenderWindow &Window, bool hitDebug);
};

#endif