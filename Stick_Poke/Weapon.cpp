#include "Weapon.h"

sf::Vector2f Weapon::GetHitVector()
{
	sf::Vector2f hitVec = m_HitCircle.getPosition() - m_OldHitboxPos;
	
	return sf::Vector2f(hitVec.x * 100, hitVec.y * 100);
}

Weapon::Weapon()
{
}

Weapon::Weapon(Weapon * NewWeapon)
{
	m_Position = NewWeapon->GetPosition();
	m_HitboxOffset = NewWeapon->GetHitboxOffset();
	m_TopSpeed = NewWeapon->GetTopSpeed();
	m_CurrentSpeed = m_TopSpeed;
	m_Circle = NewWeapon->GetCircle();
	m_ControlCircle = NewWeapon->GetControlCircle();
	m_AnchorCircle = NewWeapon->GetAnchorCircle();
	m_FrontHandCircle = NewWeapon->GetFrontHandCircle();
	m_BackHandCircle = NewWeapon->GetBackHandCircle();
	m_TargetCircle = NewWeapon->GetTargetCircle();
	m_WeaponRect = NewWeapon->GetWeaponRect();
	m_FrontHandOffset = GetFrontHandOffset();
	m_BackHandOffset = GetBackHandOffset();
	m_Body = NewWeapon->GetBody();
}

Weapon::Weapon(b2World &World)
{
	m_Position = sf::Vector2f(0, 0);
	float halfRadius = DEFAULT_RADIUS / 2;
	m_HitboxOffset = sf::Vector2f(0.0f, 0.0f);
	m_TopSpeed = 50;
	m_CurrentSpeed = m_TopSpeed;

	m_Circle.setRadius(DEFAULT_RADIUS);
	m_Circle.setOrigin(halfRadius, halfRadius);
	m_Circle.setFillColor(sf::Color::Transparent);
	m_Circle.setOutlineColor(sf::Color::White);
	m_Circle.setOutlineThickness(1.0f);
	m_Circle.setPosition(m_Position.x + halfRadius, m_Position.y + halfRadius);

	m_ControlPos = sf::Vector2f(m_Circle.getPosition().x + halfRadius, m_Circle.getPosition().y + halfRadius);
	m_ControlOffset = sf::Vector2f(DEFAULT_RADIUS + 25, 0.0f);
	m_AnchorPos = sf::Vector2f(m_Circle.getPosition().x + halfRadius, m_Circle.getPosition().y + halfRadius);
	m_AnchorOffset = sf::Vector2f(-DEFAULT_RADIUS, 0.0f);
	m_FrontHandOffset = 75;
	m_BackHandOffset = 140;

	m_ControlCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_ControlCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_ControlCircle.setFillColor(sf::Color::Blue);
	m_ControlCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_ControlCircle.setPosition(m_ControlPos);

	m_TargetCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_TargetCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_TargetCircle.setFillColor(sf::Color::Transparent);
	m_TargetCircle.setOutlineColor(sf::Color::Yellow);
	m_TargetCircle.setOutlineThickness(1);
	m_TargetCircle.setPosition(m_TargetPos);

	m_AnchorCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_AnchorCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_AnchorCircle.setFillColor(sf::Color::Red);
	m_AnchorCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_AnchorCircle.setPosition(m_AnchorPos);

	m_FrontHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_FrontHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_FrontHandCircle.setFillColor(sf::Color::Cyan);
	m_FrontHandCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_FrontHandCircle.setPosition(m_AnchorPos);

	m_BackHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_BackHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_BackHandCircle.setFillColor(sf::Color::Magenta);
	m_BackHandCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_BackHandCircle.setPosition(m_AnchorPos);

	m_WeaponRect.setSize(sf::Vector2f(DEFAULT_WEAPON_WIDTH, DEFAULT_WEAPON_HEIGHT));
	m_WeaponRect.setOrigin(sf::Vector2f(DEFAULT_WEAPON_WIDTH / 2, DEFAULT_WEAPON_HEIGHT / 2));
	m_WeaponRect.setPosition(m_ControlPos);
	m_WeaponRect.setFillColor(sf::Color::Green);

	m_HitCircle.setRadius(15.0f);
	m_HitCircle.setOrigin(15.0f, 15.0f);
	m_HitCircle.setFillColor(sf::Color(255, 0, 0, 100));
	m_HitCircle.setPosition(m_WeaponRect.getPosition() + m_HitboxOffset);
	
	InitCircularBody(World, DEFAULT_DEBUG_RADIUS);
	m_Body->SetGravityScale(0);
	m_Body->SetBullet(true);
	m_Body->SetUserData((void*)ut::b_Weapon);
	m_Body->GetFixtureList()->SetSensor(true);
	m_Body->GetFixtureList()->SetUserData((void*)ut::f_Hitbox);
	m_Body->SetSleepingAllowed(false);
}

Weapon::Weapon(b2World &World, float radius, sf::Vector2f CirclePos, sf::Vector2f ControlOffset, sf::Vector2f AnchorPos, sf::Vector2f AnchorOffset, sf::Vector2f WeaponSize, sf::Vector2f WeaponOrigin, sf::Vector2f HitBoxOffset)
{
	m_Position = sf::Vector2f(0,0);

	float halfRadius = radius / 2;
	float circleX = m_Circle.getPosition().x;
	float circleY = m_Circle.getPosition().y;
	m_HitboxOffset = HitBoxOffset;
	m_TopSpeed = 50;
	m_CurrentSpeed = m_TopSpeed;

	m_Circle.setRadius(radius);
	m_Circle.setOrigin(halfRadius, halfRadius);
	m_Circle.setFillColor(sf::Color::Transparent);
	m_Circle.setOutlineColor(sf::Color::White);
	m_Circle.setOutlineThickness(1.0f);
	m_Circle.setPosition(m_Position.x + CirclePos.x - (halfRadius), m_Position.y + CirclePos.y - (halfRadius));

	m_ControlPos = sf::Vector2f(circleX + (halfRadius), circleY + (halfRadius));
	m_ControlOffset = ControlOffset;
	m_AnchorPos = sf::Vector2f(circleX + (halfRadius) + AnchorPos.x, circleY + (halfRadius) + AnchorPos.y);
	m_AnchorOffset = AnchorOffset;
	m_FrontHandOffset = 50;
	m_BackHandOffset = 115;

	m_ControlCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_ControlCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_ControlCircle.setFillColor(sf::Color::Blue);
	m_ControlCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_ControlCircle.setPosition(m_ControlPos);

	m_TargetCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_TargetCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_TargetCircle.setFillColor(sf::Color::Transparent);
	m_TargetCircle.setOutlineColor(sf::Color::Yellow);
	m_TargetCircle.setOutlineThickness(1);
	m_TargetCircle.setPosition(m_TargetPos);

	m_AnchorCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_AnchorCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_AnchorCircle.setFillColor(sf::Color::Red);
	m_AnchorCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_AnchorCircle.setPosition(m_AnchorPos);

	m_FrontHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_FrontHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_FrontHandCircle.setFillColor(sf::Color::Cyan);
	m_FrontHandCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_FrontHandCircle.setPosition(m_AnchorPos);

	m_BackHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_BackHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_BackHandCircle.setFillColor(sf::Color::Magenta);
	m_BackHandCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_BackHandCircle.setPosition(m_AnchorPos);

	m_WeaponRect.setSize(WeaponSize);
	m_WeaponRect.setOrigin(WeaponOrigin);
	m_WeaponRect.setPosition(m_ControlPos);
	m_WeaponRect.setFillColor(sf::Color::Green);

	m_HitCircle.setRadius(15.0f);
	m_HitCircle.setOrigin(15.0f, 15.0f);
	m_HitCircle.setFillColor(sf::Color(255, 0, 0, 100));
	m_HitCircle.setPosition(m_WeaponRect.getPosition() + m_HitboxOffset);

	InitCircularBody(World, DEFAULT_DEBUG_RADIUS);
	m_Body->SetGravityScale(0);
	m_Body->SetUserData((void*)ut::b_Weapon);
	m_Body->GetFixtureList()->SetSensor(true);
	m_Body->GetFixtureList()->SetUserData((void*)ut::f_Hitbox);
	m_Body->SetSleepingAllowed(false);
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
	desiredVelocity = sf::Vector2f(desiredVelocity.x * m_CurrentSpeed, desiredVelocity.y * m_CurrentSpeed);
	desiredVelocity = Utility::Truncate(desiredVelocity, _distance);

	sf::Vector2f result = Current + desiredVelocity;

	return result;
}

void Weapon::Update(sf::Vector2f ControlPos, sf::Vector2f CharPos, sf::Vector2f CharSize, bool Flip, bool AllowFlip)
{
	m_Flip = Flip;

	if(m_Flip)
	{
		m_Circle.setPosition(CharPos.x - m_TargetOffset.x, CharPos.y + m_TargetOffset.y);

		m_AnchorPos = CharPos;
		m_AnchorPos += sf::Vector2f(-m_AnchorOffset.x, m_AnchorOffset.y);
		m_AnchorCircle.setPosition(m_AnchorPos);

		m_TargetPos = CharPos;
		m_TargetPos += sf::Vector2f(-m_TargetOffset.x + (ControlPos.x / 100 * m_Circle.getRadius()), m_TargetOffset.y + (ControlPos.y / 100 * m_Circle.getRadius()));
		m_TargetCircle.setPosition(m_TargetPos);

		m_ControlOffset = -m_ControlPos + m_OldCharPos;

		m_ControlPos = CharPos;
		m_ControlPos -= m_ControlOffset;
		m_ControlPos = Seek(m_TargetPos, m_ControlPos);
		m_ControlCircle.setPosition(m_ControlPos);

		float distance = 0;
		float ratio = 0;

		switch (m_Grip)
		{
		default:
		case G_TWOHAND:
			distance = Utility::GetMagnitude(m_ControlPos - m_AnchorPos);

			ratio = m_FrontHandOffset / distance;

			m_FrontHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
			m_FrontHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

			if (m_FrontHandPos.x > CharPos.x - (CharSize.x / 2))
			{
				float newOffset = m_FrontHandOffset + ((CharPos.x - (CharSize.x / 2)) - m_FrontHandPos.x);

				ratio = newOffset / distance;

				m_FrontHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
				m_FrontHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);
			}

			ratio = m_BackHandOffset / distance;

			m_BackHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
			m_BackHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

			m_FrontHandCircle.setPosition(m_BackHandPos);
			m_BackHandCircle.setPosition(m_FrontHandPos);
			break;
		case G_FRONTHAND:
			distance = Utility::GetMagnitude(m_ControlPos - m_AnchorPos);

			ratio = m_FrontHandOffset / distance;

			m_FrontHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
			m_FrontHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

			m_BackHandCircle.setPosition(m_FrontHandPos);
			break;
		case G_BACKHAND:
			distance = Utility::GetMagnitude(m_ControlPos - m_AnchorPos);

			ratio = m_BackHandOffset / distance;

			m_BackHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
			m_BackHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

			m_FrontHandCircle.setPosition(m_BackHandPos);
			break;
		}
	}
	else
	{
		m_Circle.setPosition(CharPos.x + m_TargetOffset.x, CharPos.y + m_TargetOffset.y);

		m_AnchorPos = CharPos;
		m_AnchorPos += m_AnchorOffset;
		m_AnchorCircle.setPosition(m_AnchorPos);

		m_TargetPos = CharPos;
		m_TargetPos += sf::Vector2f(m_TargetOffset.x + (ControlPos.x / 100 * m_Circle.getRadius()), m_TargetOffset.y + (ControlPos.y / 100 * m_Circle.getRadius()));
		m_TargetCircle.setPosition(m_TargetPos);
		
		m_ControlOffset = m_ControlPos - m_OldCharPos;

		m_ControlPos = CharPos;
		m_ControlPos += m_ControlOffset;
		m_ControlPos = Seek(m_TargetPos, m_ControlPos);
		m_ControlCircle.setPosition(m_ControlPos);

		float distance = 0;
		float ratio = 0;

		switch (m_Grip)
		{
		default:
		case G_TWOHAND:
			distance = Utility::GetMagnitude(m_ControlPos - m_AnchorPos);

			ratio = m_FrontHandOffset / distance;

			m_FrontHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
			m_FrontHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

			if (m_FrontHandPos.x < CharPos.x + (CharSize.x / 2))
			{
				float newOffset = m_FrontHandOffset - ((CharPos.x + (CharSize.x / 2)) - m_FrontHandPos.x);

				ratio = newOffset / distance;

				m_FrontHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
				m_FrontHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);
			}

			ratio = m_BackHandOffset / distance;

			m_BackHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
			m_BackHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

			m_FrontHandCircle.setPosition(m_FrontHandPos);
			m_BackHandCircle.setPosition(m_BackHandPos);
			break;
		case G_FRONTHAND:
			distance = Utility::GetMagnitude(m_ControlPos - m_AnchorPos);

			ratio = m_FrontHandOffset / distance;

			m_FrontHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
			m_FrontHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

			m_FrontHandCircle.setPosition(m_FrontHandPos);
			break;
		case G_BACKHAND:
			distance = Utility::GetMagnitude(m_ControlPos - m_AnchorPos);

			ratio = m_BackHandOffset / distance;

			m_BackHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
			m_BackHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

			m_BackHandCircle.setPosition(m_BackHandPos);
			break;
		}
	}

	float opposite = m_ControlCircle.getPosition().x - m_AnchorCircle.getPosition().x;
	float adjacent = m_ControlCircle.getPosition().y - m_AnchorCircle.getPosition().y;

	if (opposite > 0)
		m_WeaponRect.setRotation((atan(adjacent / opposite)) * 180 / ut::PI);
	else
		m_WeaponRect.setRotation(((atan(adjacent / opposite)) * 180 / ut::PI) + 180);

	m_WeaponRect.setPosition(m_ControlCircle.getPosition().x, m_ControlCircle.getPosition().y);

	m_OldHitboxPos = m_HitCircle.getPosition();

	m_HitCircle.setPosition( 
		(m_HitboxOffset.x * cos(m_WeaponRect.getRotation() / 180 * ut::PI)) - (m_HitboxOffset.y * sin(m_WeaponRect.getRotation() / 180 * ut::PI)) + m_WeaponRect.getPosition().x,
		(m_HitboxOffset.x * sin(m_WeaponRect.getRotation() / 180 * ut::PI)) + (m_HitboxOffset.y * cos(m_WeaponRect.getRotation() / 180 * ut::PI)) + m_WeaponRect.getPosition().y
	);

	m_Body->SetTransform(Utility::SFVECtoB2VEC(m_HitCircle.getPosition(), true), 0);

	m_OldCharPos = CharPos;
}


void Weapon::Draw(sf::RenderWindow &Window, bool hitDebug)
{
	Window.draw(m_WeaponRect);
	if(hitDebug)
	{
		Window.draw(m_Circle);
		Window.draw(m_TargetCircle);
		Window.draw(m_ControlCircle);
		Window.draw(m_TargetCircle);
		Window.draw(m_AnchorCircle);
		Window.draw(m_HitCircle);
	}

	if (m_Flip)
	{
		if (m_Grip == G_TWOHAND || m_Grip == G_FRONTHAND)
			Window.draw(m_BackHandCircle);

		if (m_Grip == G_TWOHAND || m_Grip == G_BACKHAND)
			Window.draw(m_FrontHandCircle);
	}
	else
	{
		if (m_Grip == G_TWOHAND || m_Grip == G_FRONTHAND)
			Window.draw(m_FrontHandCircle);

		if (m_Grip == G_TWOHAND || m_Grip == G_BACKHAND)
			Window.draw(m_BackHandCircle);
	}
}