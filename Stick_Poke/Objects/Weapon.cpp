#include "Weapon.h"


Weapon::Weapon()
{
	m_Position = Vector2f(0, 0);
	float halfRadius = DEFAULT_RADIUS / 2;
	m_HitboxOffset = Vector2f(0.0f, 0.0f);

	m_Circle.setRadius(DEFAULT_RADIUS);
	m_Circle.setOrigin(halfRadius, halfRadius);
	m_Circle.setFillColor(Color::Transparent);
	m_Circle.setOutlineColor(Color::White);
	m_Circle.setOutlineThickness(1.0f);
	m_Circle.setPosition(m_Position.x + DEFAULT_RADIUS - (halfRadius), m_Position.y + DEFAULT_RADIUS - (halfRadius));

	m_ControlPos = Vector2f(m_Circle.getPosition().x + (halfRadius), m_Circle.getPosition().y + (halfRadius));
	m_ControlOffset = Vector2f(DEFAULT_RADIUS, 0.0f);
	m_AnchorPos = Vector2f(m_Circle.getPosition().x + (halfRadius), m_Circle.getPosition().y + (halfRadius));
	m_AnchorOffset = Vector2f(-DEFAULT_RADIUS, 0.0f);
	m_FrontHandOffset = 50;
	m_BackHandOffset = 100;

	m_ControlCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_ControlCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_ControlCircle.setFillColor(Color::Blue);
	m_ControlCircle.setOutlineColor(Color(0, 0, 0, 0));
	m_ControlCircle.setPosition(m_ControlPos);

	m_AnchorCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_AnchorCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_AnchorCircle.setFillColor(Color::Red);
	m_AnchorCircle.setOutlineColor(Color(0, 0, 0, 0));
	m_AnchorCircle.setPosition(m_AnchorPos);

	m_FrontHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_FrontHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_FrontHandCircle.setFillColor(Color::Cyan);
	m_FrontHandCircle.setOutlineColor(Color(0, 0, 0, 0));
	m_FrontHandCircle.setPosition(m_AnchorPos);

	m_BackHandCircle.setRadius(DEFAULT_DEBUG_RADIUS);
	m_BackHandCircle.setOrigin(DEFAULT_DEBUG_RADIUS, DEFAULT_DEBUG_RADIUS);
	m_BackHandCircle.setFillColor(Color::Magenta);
	m_BackHandCircle.setOutlineColor(Color(0, 0, 0, 0));
	m_BackHandCircle.setPosition(m_AnchorPos);

	m_WeaponRect.setSize(Vector2f(DEFAULT_WEAPON_WIDTH, DEFAULT_WEAPON_HEIGHT));
	m_WeaponRect.setOrigin(Vector2f(DEFAULT_WEAPON_WIDTH / 2, DEFAULT_WEAPON_HEIGHT / 2));
	m_WeaponRect.setPosition(m_ControlPos);
	m_WeaponRect.setFillColor(Color::Green);

	m_HitCircle.setRadius(15.0f);
	m_HitCircle.setOrigin(15.0f, 15.0f);
	m_HitCircle.setFillColor(Color(255, 0, 0, 100));
	m_HitCircle.setPosition(m_WeaponRect.getPosition() + m_HitboxOffset);
}

Weapon::Weapon(float radius, Vector2f CirclePos, Vector2f ControlOffset, Vector2f AnchorPos, Vector2f AnchorOffset, Vector2f WeaponSize, Vector2f WeaponOrigin, Vector2f HitBoxOffset)
{
	m_Position = Vector2f(0,0);

	float halfRadius = radius / 2;
	float circleX = m_Circle.getPosition().x;
	float circleY = m_Circle.getPosition().y;
	m_HitboxOffset = HitBoxOffset;

	m_Circle.setRadius(radius);
	m_Circle.setOrigin(halfRadius, halfRadius);
	m_Circle.setFillColor(Color::Transparent);
	m_Circle.setOutlineColor(Color::White);
	m_Circle.setOutlineThickness(1.0f);
	m_Circle.setPosition(m_Position.x + CirclePos.x - (halfRadius), m_Position.y + CirclePos.y - (halfRadius));

	m_ControlPos = Vector2f(circleX + (halfRadius), circleY + (halfRadius));
	m_ControlOffset = ControlOffset;
	m_AnchorPos = Vector2f(circleX + (halfRadius) + AnchorPos.x, circleY + (halfRadius) + AnchorPos.y);
	m_AnchorOffset = AnchorOffset;
	m_FrontHandOffset = 50;
	m_BackHandOffset = 100;

	m_ControlCircle.setRadius(4.0f);
	m_ControlCircle.setOrigin(4.0f, 4.0f);
	m_ControlCircle.setFillColor(Color::Blue);
	m_ControlCircle.setOutlineColor(Color(0, 0, 0, 0));
	m_ControlCircle.setPosition(m_ControlPos);

	m_AnchorCircle.setRadius(4.0f);
	m_AnchorCircle.setOrigin(4.0f, 4.0f);
	m_AnchorCircle.setFillColor(Color::Red);
	m_AnchorCircle.setOutlineColor(Color(0, 0, 0, 0));
	m_AnchorCircle.setPosition(m_AnchorPos);

	m_FrontHandCircle.setRadius(4.0f);
	m_FrontHandCircle.setOrigin(4.0f, 4.0f);
	m_FrontHandCircle.setFillColor(Color::Cyan);
	m_FrontHandCircle.setOutlineColor(Color(0, 0, 0, 0));
	m_FrontHandCircle.setPosition(m_AnchorPos);

	m_BackHandCircle.setRadius(4.0f);
	m_BackHandCircle.setOrigin(4.0f, 4.0f);
	m_BackHandCircle.setFillColor(Color::Magenta);
	m_BackHandCircle.setOutlineColor(Color(0, 0, 0, 0));
	m_BackHandCircle.setPosition(m_AnchorPos);

	m_WeaponRect.setSize(WeaponSize);
	m_WeaponRect.setOrigin(WeaponOrigin);
	m_WeaponRect.setPosition(m_ControlPos);
	m_WeaponRect.setFillColor(Color::Green);

	m_HitCircle.setRadius(15.0f);
	m_HitCircle.setOrigin(15.0f, 15.0f);
	m_HitCircle.setFillColor(Color(255, 0, 0, 100));
	m_HitCircle.setPosition(m_WeaponRect.getPosition() + m_HitboxOffset);

}


Weapon::~Weapon()
{
}

void Weapon::Update(Vector2f ControlPos, Vector2f CharPos, bool Flip, bool AllowFlip)
{
	flip = Flip;

	if(flip)
	{
		m_Circle.setPosition(CharPos.x - m_ControlOffset.x, CharPos.y + m_ControlOffset.y);

		m_AnchorPos = Vector2f(CharPos.x - m_AnchorOffset.x, CharPos.y + m_AnchorOffset.y);
		m_AnchorCircle.setPosition(m_AnchorPos);
		m_ControlPos = Vector2f(-m_ControlOffset.x + CharPos.x + (ControlPos.x / 100 * m_Circle.getRadius()), m_ControlOffset.y + CharPos.y + (ControlPos.y / 100 * m_Circle.getRadius()));
		m_ControlCircle.setPosition(m_ControlPos);
	}
	else
	{
		m_Circle.setPosition(CharPos.x + m_ControlOffset.x, CharPos.y + m_ControlOffset.y);

		m_AnchorPos = Vector2f(CharPos.x + m_AnchorOffset.x, CharPos.y + m_AnchorOffset.y);
		m_AnchorCircle.setPosition(m_AnchorPos);
		m_ControlPos = Vector2f(m_ControlOffset.x + CharPos.x + (ControlPos.x / 100 * m_Circle.getRadius()), m_ControlOffset.y + CharPos.y + (ControlPos.y / 100 * m_Circle.getRadius()));
		m_ControlCircle.setPosition(m_ControlPos);
		
		float distance = sqrt(((m_ControlPos.x - m_AnchorPos.x)*(m_ControlPos.x - m_AnchorPos.x)) + ((m_ControlPos.y - m_AnchorPos.y)*(m_ControlPos.y - m_AnchorPos.y)));
		float ratio = m_FrontHandOffset / distance;

		m_FrontHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
		m_FrontHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);
		
		ratio = m_BackHandOffset / distance;

		m_BackHandPos.x = (ratio * m_AnchorPos.x + (1 - ratio) *  m_ControlPos.x);
		m_BackHandPos.y = (ratio * m_AnchorPos.y + (1 - ratio) *  m_ControlPos.y);

		m_FrontHandCircle.setPosition(m_FrontHandPos);
		m_BackHandCircle.setPosition(m_BackHandPos);
	}

	float opposite = m_ControlCircle.getPosition().x - m_AnchorCircle.getPosition().x;
	float adjacent = m_ControlCircle.getPosition().y - m_AnchorCircle.getPosition().y;

	if(opposite > 0)
		m_WeaponRect.setRotation((atan(adjacent / opposite)) * 180 / b2_pi);
	else
		m_WeaponRect.setRotation(((atan(adjacent / opposite)) * 180 / b2_pi) + 180);

	m_WeaponRect.setPosition(m_ControlCircle.getPosition().x, m_ControlCircle.getPosition().y);

	m_HitCircle.setPosition( //Try to get otherHitBoxOffset working
		(m_HitboxOffset.x * cos(m_WeaponRect.getRotation() / 180 * b2_pi)) - (m_HitboxOffset.y * sin(m_WeaponRect.getRotation() / 180 * b2_pi)) + m_WeaponRect.getPosition().x,
		(m_HitboxOffset.x * sin(m_WeaponRect.getRotation() / 180 * b2_pi)) + (m_HitboxOffset.y * cos(m_WeaponRect.getRotation() / 180 * b2_pi)) + m_WeaponRect.getPosition().y
	);
}


void Weapon::Draw(RenderWindow &Window, bool hitDebug)
{
	Window.draw(m_WeaponRect);
	if(hitDebug)
	{
		Window.draw(m_Circle);
		Window.draw(m_ControlCircle);
		Window.draw(m_AnchorCircle);
		Window.draw(m_FrontHandCircle);
		Window.draw(m_BackHandCircle);
		Window.draw(m_HitCircle);
	}
}