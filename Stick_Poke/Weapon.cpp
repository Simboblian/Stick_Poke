#include "Weapon.h"

sf::Vector2f Weapon::GetHitVector()
{
	sf::Vector2f hitVec = _hitCircle.getPosition() - _oldHitboxPos;
	
	return sf::Vector2f(hitVec.x * 100, hitVec.y * 100);
}

Weapon::Weapon()
{
}

Weapon::Weapon(Weapon * NewWeapon)
{
	_position = NewWeapon->GetPosition();
	_hitboxOffset = NewWeapon->GetHitboxOffset();
	_topSpeed = NewWeapon->GetTopSpeed();
	_currentSpeed = _topSpeed;
	_circle = NewWeapon->GetCircle();
	_controlCircle = NewWeapon->GetControlCircle();
	_anchorCircle = NewWeapon->GetAnchorCircle();
	_frontHandCircle = NewWeapon->GetFrontHandCircle();
	_backHandCircle = NewWeapon->GetBackHandCircle();
	_targetCircle = NewWeapon->GetTargetCircle();
	_weaponRect = NewWeapon->GetWeaponRect();
	_frontHandOffset = GetFrontHandOffset();
	_backHandOffset = GetBackHandOffset();
	_body = NewWeapon->GetBody();
}

Weapon::Weapon(b2World &World)
{
	_position = sf::Vector2f(0, 0);
	float halfRadius = DEFAULT_RADIUS / 2;
	_hitboxOffset = sf::Vector2f(0.0f, 0.0f);
	_topSpeed = 50;
	_currentSpeed = _topSpeed;

	_circle.setRadius(DEFAULT_RADIUS);
	_circle.setOrigin(halfRadius, halfRadius);
	_circle.setFillColor(sf::Color::Transparent);
	_circle.setOutlineColor(sf::Color::White);
	_circle.setOutlineThickness(1.0f);
	_circle.setPosition(_position.x + halfRadius, _position.y + halfRadius);

	_controlPos = sf::Vector2f(_circle.getPosition().x + halfRadius, _circle.getPosition().y + halfRadius);
	_controlOffset = sf::Vector2f(DEFAULT_RADIUS + 25, 0.0f);
	_anchorPos = sf::Vector2f(_circle.getPosition().x + halfRadius, _circle.getPosition().y + halfRadius);
	_anchorOffset = sf::Vector2f(-DEFAULT_RADIUS, 0.0f);
	_frontHandOffset = 75;
	_backHandOffset = 140;

	_controlCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_controlCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_controlCircle.setFillColor(sf::Color::Blue);
	_controlCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_controlCircle.setPosition(_controlPos);

	_targetCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_targetCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_targetCircle.setFillColor(sf::Color::Transparent);
	_targetCircle.setOutlineColor(sf::Color::Yellow);
	_targetCircle.setOutlineThickness(1);
	_targetCircle.setPosition(_targetPos);

	_anchorCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_anchorCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_anchorCircle.setFillColor(sf::Color::Red);
	_anchorCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_anchorCircle.setPosition(_anchorPos);

	_frontHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_frontHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_frontHandCircle.setFillColor(sf::Color::Cyan);
	_frontHandCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_frontHandCircle.setPosition(_anchorPos);

	_backHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_backHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_backHandCircle.setFillColor(sf::Color::Magenta);
	_backHandCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_backHandCircle.setPosition(_anchorPos);

	_weaponRect.setSize(sf::Vector2f(DEFAULT_WEAPON_WIDTH, DEFAULT_WEAPON_HEIGHT));
	_weaponRect.setOrigin(sf::Vector2f(DEFAULT_WEAPON_WIDTH / 2, DEFAULT_WEAPON_HEIGHT / 2));
	_weaponRect.setPosition(_controlPos);
	_weaponRect.setFillColor(sf::Color::Green);

	_hitCircle.setRadius(15.0f);
	_hitCircle.setOrigin(15.0f, 15.0f);
	_hitCircle.setFillColor(sf::Color(255, 0, 0, 100));
	_hitCircle.setPosition(_weaponRect.getPosition() + _hitboxOffset);
	
	InitCircularBody(World, DEFAULT_DEBUG_RADIUS);
	_body->SetGravityScale(0);
	_body->SetBullet(true);
	_body->SetUserData((void*)ut::b_Weapon);
	_body->GetFixtureList()->SetSensor(true);
	_body->GetFixtureList()->SetUserData((void*)ut::f_Hitbox);
	_body->SetSleepingAllowed(false);
}

Weapon::Weapon(b2World &World, float radius, sf::Vector2f CirclePos, sf::Vector2f ControlOffset, sf::Vector2f AnchorPos, sf::Vector2f AnchorOffset, sf::Vector2f WeaponSize, sf::Vector2f WeaponOrigin, sf::Vector2f HitBoxOffset)
{
	_position = sf::Vector2f(0,0);

	float halfRadius = radius / 2;
	float circleX = _circle.getPosition().x;
	float circleY = _circle.getPosition().y;
	_hitboxOffset = HitBoxOffset;
	_topSpeed = 50;
	_currentSpeed = _topSpeed;

	_circle.setRadius(radius);
	_circle.setOrigin(halfRadius, halfRadius);
	_circle.setFillColor(sf::Color::Transparent);
	_circle.setOutlineColor(sf::Color::White);
	_circle.setOutlineThickness(1.0f);
	_circle.setPosition(_position.x + CirclePos.x - (halfRadius), _position.y + CirclePos.y - (halfRadius));

	_controlPos = sf::Vector2f(circleX + (halfRadius), circleY + (halfRadius));
	_controlOffset = ControlOffset;
	_anchorPos = sf::Vector2f(circleX + (halfRadius) + AnchorPos.x, circleY + (halfRadius) + AnchorPos.y);
	_anchorOffset = AnchorOffset;
	_frontHandOffset = 50;
	_backHandOffset = 115;

	_controlCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_controlCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_controlCircle.setFillColor(sf::Color::Blue);
	_controlCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_controlCircle.setPosition(_controlPos);

	_targetCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_targetCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_targetCircle.setFillColor(sf::Color::Transparent);
	_targetCircle.setOutlineColor(sf::Color::Yellow);
	_targetCircle.setOutlineThickness(1);
	_targetCircle.setPosition(_targetPos);

	_anchorCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_anchorCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_anchorCircle.setFillColor(sf::Color::Red);
	_anchorCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_anchorCircle.setPosition(_anchorPos);

	_frontHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_frontHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_frontHandCircle.setFillColor(sf::Color::Cyan);
	_frontHandCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_frontHandCircle.setPosition(_anchorPos);

	_backHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	_backHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	_backHandCircle.setFillColor(sf::Color::Magenta);
	_backHandCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_backHandCircle.setPosition(_anchorPos);

	_weaponRect.setSize(WeaponSize);
	_weaponRect.setOrigin(WeaponOrigin);
	_weaponRect.setPosition(_controlPos);
	_weaponRect.setFillColor(sf::Color::Green);

	_hitCircle.setRadius(15.0f);
	_hitCircle.setOrigin(15.0f, 15.0f);
	_hitCircle.setFillColor(sf::Color(255, 0, 0, 100));
	_hitCircle.setPosition(_weaponRect.getPosition() + _hitboxOffset);

	InitCircularBody(World, DEFAULT_DEBUG_RADIUS);
	_body->SetGravityScale(0);
	_body->SetUserData((void*)ut::b_Weapon);
	_body->GetFixtureList()->SetSensor(true);
	_body->GetFixtureList()->SetUserData((void*)ut::f_Hitbox);
	_body->SetSleepingAllowed(false);
}

Weapon::~Weapon()
{
}

sf::Vector2f Weapon::Seek(sf::Vector2f Target, sf::Vector2f Current)
{
	float _distance = Utility::GetMagnitude(Target - Current);

	//-----Seeking with Arrival-----//
	// Normalise the desired velocity vector then scale it by the maximum speed.
	sf::Vector2f desiredVelocity = Utility::Normalise(Target - Current);
	desiredVelocity = sf::Vector2f(desiredVelocity.x * _currentSpeed, desiredVelocity.y * _currentSpeed);
	desiredVelocity = Utility::Truncate(desiredVelocity, _distance);

	sf::Vector2f result = Current + desiredVelocity;

	return result;
}

void Weapon::Update(sf::Vector2f ControlPos, sf::Vector2f CharPos, sf::Vector2f CharSize, bool Flip, bool AllowFlip)
{
	bool justFlipped = false;

	if (Flip != _flip)
	{
		_flip = Flip;
		justFlipped = true;
	}

	if(_flip)
	{
		_circle.setPosition(CharPos.x - _targetOffset.x, CharPos.y + _targetOffset.y);

		_anchorPos = CharPos;
		_anchorPos += sf::Vector2f(-_anchorOffset.x, _anchorOffset.y);
		_anchorCircle.setPosition(_anchorPos);

		_targetPos = CharPos;
		_targetPos += sf::Vector2f(-_targetOffset.x + (ControlPos.x / 100 * _circle.getRadius()), _targetOffset.y + (ControlPos.y / 100 * _circle.getRadius()));
		_targetCircle.setPosition(_targetPos);

		_controlOffset = -_controlPos + _oldCharPos;

		_controlPos = CharPos;
		_controlPos -= _controlOffset;
		_controlPos = Seek(_targetPos, _controlPos);
		_controlCircle.setPosition(_controlPos);

		float distance = 0;
		float ratio = 0;

		switch (_grip)
		{
		default:
		case G_TWOHAND:
			distance = Utility::GetMagnitude(_controlPos - _anchorPos);

			ratio = _frontHandOffset / distance;

			_frontHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
			_frontHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);

			if (_frontHandPos.x > CharPos.x - (CharSize.x / 2))
			{
				float newOffset = _frontHandOffset + ((CharPos.x - (CharSize.x / 2)) - _frontHandPos.x);

				ratio = newOffset / distance;

				_frontHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
				_frontHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);
			}

			ratio = _backHandOffset / distance;

			_backHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
			_backHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);

			_frontHandCircle.setPosition(_backHandPos);
			_backHandCircle.setPosition(_frontHandPos);
			break;
		case G_FRONTHAND:
			distance = Utility::GetMagnitude(_controlPos - _anchorPos);

			ratio = _frontHandOffset / distance;

			_frontHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
			_frontHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);

			_backHandCircle.setPosition(_frontHandPos);
			break;
		case G_BACKHAND:
			distance = Utility::GetMagnitude(_controlPos - _anchorPos);

			ratio = _backHandOffset / distance;

			_backHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
			_backHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);

			_frontHandCircle.setPosition(_backHandPos);
			break;
		}
	}
	else
	{
		_circle.setPosition(CharPos.x + _targetOffset.x, CharPos.y + _targetOffset.y);

		_anchorPos = CharPos;
		_anchorPos += _anchorOffset;
		_anchorCircle.setPosition(_anchorPos);

		_targetPos = CharPos;
		_targetPos += sf::Vector2f(_targetOffset.x + (ControlPos.x / 100 * _circle.getRadius()), _targetOffset.y + (ControlPos.y / 100 * _circle.getRadius()));
		_targetCircle.setPosition(_targetPos);

		_controlOffset = _controlPos - _oldCharPos;

		_controlPos = CharPos;
		_controlPos += _controlOffset;
		_controlPos = Seek(_targetPos, _controlPos);
		_controlCircle.setPosition(_controlPos);

		float distance = 0;
		float ratio = 0;

		switch (_grip)
		{
		default:
		case G_TWOHAND:
			distance = Utility::GetMagnitude(_controlPos - _anchorPos);

			ratio = _frontHandOffset / distance;

			_frontHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
			_frontHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);

			if (_frontHandPos.x < CharPos.x + (CharSize.x / 2))
			{
				float newOffset = _frontHandOffset - ((CharPos.x + (CharSize.x / 2)) - _frontHandPos.x);

				ratio = newOffset / distance;

				_frontHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
				_frontHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);
			}

			ratio = _backHandOffset / distance;

			_backHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
			_backHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);

			_frontHandCircle.setPosition(_frontHandPos);
			_backHandCircle.setPosition(_backHandPos);
			break;
		case G_FRONTHAND:
			distance = Utility::GetMagnitude(_controlPos - _anchorPos);

			ratio = _frontHandOffset / distance;

			_frontHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
			_frontHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);

			_frontHandCircle.setPosition(_frontHandPos);
			break;
		case G_BACKHAND:
			distance = Utility::GetMagnitude(_controlPos - _anchorPos);

			ratio = _backHandOffset / distance;

			_backHandPos.x = (ratio * _anchorPos.x + (1 - ratio) *  _controlPos.x);
			_backHandPos.y = (ratio * _anchorPos.y + (1 - ratio) *  _controlPos.y);

			_backHandCircle.setPosition(_backHandPos);
			break;
		}
	}

	float opposite = _controlCircle.getPosition().x - _anchorCircle.getPosition().x;
	float adjacent = _controlCircle.getPosition().y - _anchorCircle.getPosition().y;

	if (opposite > 0)
		_weaponRect.setRotation((atan(adjacent / opposite)) * 180 / ut::PI);
	else
		_weaponRect.setRotation(((atan(adjacent / opposite)) * 180 / ut::PI) + 180);

	_weaponRect.setPosition(_controlCircle.getPosition().x, _controlCircle.getPosition().y);

	_oldHitboxPos = _hitCircle.getPosition();

	_hitCircle.setPosition( 
		(_hitboxOffset.x * cos(_weaponRect.getRotation() / 180 * ut::PI)) - (_hitboxOffset.y * sin(_weaponRect.getRotation() / 180 * ut::PI)) + _weaponRect.getPosition().x,
		(_hitboxOffset.x * sin(_weaponRect.getRotation() / 180 * ut::PI)) + (_hitboxOffset.y * cos(_weaponRect.getRotation() / 180 * ut::PI)) + _weaponRect.getPosition().y
	);

	_body->SetTransform(Utility::SFVECtoB2VEC(_hitCircle.getPosition(), true), 0);

	_oldCharPos = CharPos;
}

void Weapon::UpdateHandPosition(Grip CURRENTGRIP)
{
}


void Weapon::Draw(sf::RenderWindow &Window, bool hitDebug)
{
	Window.draw(_weaponRect);

	if (_flip)
	{
		if (_grip == G_TWOHAND || _grip == G_FRONTHAND)
			Window.draw(_backHandCircle);

		if (_grip == G_TWOHAND || _grip == G_BACKHAND)
			Window.draw(_frontHandCircle);
	}
	else
	{
		if (_grip == G_TWOHAND || _grip == G_FRONTHAND)
			Window.draw(_frontHandCircle);

		if (_grip == G_TWOHAND || _grip == G_BACKHAND)
			Window.draw(_backHandCircle);
	}

	if(hitDebug)
	{
		Window.draw(_circle);
		Window.draw(_targetCircle);
		Window.draw(_controlCircle);
		Window.draw(_targetCircle);
		Window.draw(_anchorCircle);
		Window.draw(_hitCircle);
	}

}