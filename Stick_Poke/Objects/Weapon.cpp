#include "Weapon.h"


Weapon::Weapon(float radius, Vector2f CirclePos, Vector2f ControlOffset, Vector2f AnchorPos, Vector2f AnchorOffset, Vector2f WeaponSize, Vector2f WeaponOrigin, float HitBoxOffset)
{
	m_Position = Vector2f(0,0);

	float halfRadius = radius / 2;
	float circleX = m_Circle.getPosition().x;
	float circleY = m_Circle.getPosition().y;
	hitBoxOffset = HitBoxOffset;

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

	m_WeaponRect.setSize(WeaponSize);
	m_WeaponRect.setOrigin(WeaponOrigin);
	m_WeaponRect.setPosition(m_ControlPos);
	m_WeaponRect.setFillColor(Color::Green);

	m_HitCircle.setRadius(15.0f);
	m_HitCircle.setOrigin(15.0f, 15.0f);
	m_HitCircle.setFillColor(Color(255, 0, 0, 100));
	m_HitCircle.setPosition(m_WeaponRect.getPosition().x + hitBoxOffset, m_WeaponRect.getPosition().y);
}


Weapon::~Weapon()
{
}

void Weapon::AddPhysics(b2World& World, int index)
{
	//Create Weapon Body
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(m_WeaponRect.getPosition().x/SCALE, m_WeaponRect.getPosition().y/SCALE);
	BodyDef.type = b2_dynamicBody;
	m_Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_WeaponRect.getSize().x/2)/SCALE, (m_WeaponRect.getSize().y/2)/SCALE,
		b2Vec2(-m_WeaponRect.getOrigin().x/SCALE + (m_WeaponRect.getSize().x/2)/SCALE, -m_WeaponRect.getOrigin().y/SCALE + (m_WeaponRect.getSize().y/2)/SCALE),
		0.0f);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 20.0f;
	FixtureDef.friction = 1.0f;
	FixtureDef.shape = &Shape;
	FixtureDef.userData = &index;
	FixtureDef.filter.groupIndex = -2;
	FixtureDef.isSensor = true;
	m_Body->SetFixedRotation(false);
	m_Body->CreateFixture(&FixtureDef);

	//set up chain links
	BodyDef.type = b2_dynamicBody;
	BodyDef.position = b2Vec2_zero;
	Shape.SetAsBox(10/SCALE, 2/SCALE);
	FixtureDef.shape = &Shape;
	FixtureDef.isSensor = false;
	FixtureDef.density = 50.0f;
	FixtureDef.friction = 1.0f;
}

void Weapon::AddChainLink(b2World& World, b2Body& PrevBody)
{

}

void Weapon::OldAddPhysics(b2World& World, int index)
{
	//Create Anchor Body
	b2BodyDef AnchorBodyDef;
	AnchorBodyDef.position = b2Vec2(m_AnchorPos.x/SCALE, m_AnchorPos.y/SCALE);
	AnchorBodyDef.type = b2_kinematicBody;
	m_AnchorBody = World.CreateBody(&AnchorBodyDef);

	b2CircleShape CShape;
	CShape.m_radius = 2.0f/SCALE;
	b2FixtureDef AnchorFixtureDef;
	AnchorFixtureDef.density = 10.0f;
	AnchorFixtureDef.friction = 1.0f;
	AnchorFixtureDef.shape = &CShape;
	AnchorFixtureDef.userData = &index;
	AnchorFixtureDef.filter.groupIndex = index;
	m_AnchorBody->SetFixedRotation(true);
	m_AnchorBody->CreateFixture(&AnchorFixtureDef);

	//Create Control Body
	b2BodyDef ControlBodyDef;
	ControlBodyDef.position = b2Vec2(m_ControlPos.x/SCALE, m_ControlPos.y/SCALE);
	ControlBodyDef.type = b2_kinematicBody;
	m_ControlBody = World.CreateBody(&ControlBodyDef);

	b2FixtureDef ControlFixtureDef;
	ControlFixtureDef.density = 10.0f;
	ControlFixtureDef.friction = 1.0f;
	ControlFixtureDef.shape = &CShape;
	ControlFixtureDef.userData = &index;
	ControlFixtureDef.filter.groupIndex = index;
	m_ControlBody->SetFixedRotation(true);
	m_ControlBody->CreateFixture(&ControlFixtureDef);

	//Create Weapon Body
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(m_WeaponRect.getPosition().x/SCALE, m_WeaponRect.getPosition().y/SCALE);
	BodyDef.type = b2_dynamicBody;
	m_Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_WeaponRect.getSize().x/2)/SCALE, (m_WeaponRect.getSize().y/2)/SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 10.0f;
	FixtureDef.friction = 1.0f;
	FixtureDef.shape = &Shape;
	FixtureDef.userData = &index;
	FixtureDef.filter.groupIndex = index;
	m_Body->SetFixedRotation(false);
	m_Body->CreateFixture(&FixtureDef);
	m_Body->IsBullet();

	//Outline Join for Anchor
	b2WeldJointDef AnchorJointDef;
	AnchorJointDef.bodyA = m_Body;
	AnchorJointDef.bodyB = m_AnchorBody;
	AnchorJointDef.frequencyHz = 30.0f;
	AnchorJointDef.dampingRatio = 1.0f;
	AnchorJointDef.localAnchorA = b2Vec2(((-m_WeaponRect.getSize().x - 10) / 2)/SCALE, 0.0f);
	AnchorJointDef.localAnchorB = b2Vec2(((-m_WeaponRect.getSize().x - 10) / 2)/SCALE, 0.0f);
	//AnchorJointDef.localAnchorA = b2Vec2((-weaponRect.getSize().x /2)/SCALE, 0.0f);
	AnchorJointDef.collideConnected = false;

	//Outline Join for Control
	b2WeldJointDef ControlJointDef;
	ControlJointDef.bodyA = m_Body;
	ControlJointDef.bodyB = m_ControlBody;
	ControlJointDef.frequencyHz = 30.0f;
	ControlJointDef.dampingRatio = 1.0f;
	ControlJointDef.localAnchorA = b2Vec2(((-m_WeaponRect.getSize().x)/2)/SCALE, 0.0f);
	ControlJointDef.localAnchorB = b2Vec2(((-m_WeaponRect.getSize().x)/2)/SCALE, 0.0f);
	//ControlJointDef.localAnchorA = b2Vec2(((weaponRect.getSize().x - 50)/2)/SCALE, 0.0f);
	ControlJointDef.collideConnected = false;

	World.CreateJoint(&ControlJointDef);
	World.CreateJoint(&AnchorJointDef);
}


void Weapon::Update(Vector2f ControlPos, Vector2f CharPos, bool Flip, bool AllowFlip)
{
	flip = Flip;

	if(flip)
	{
		m_Circle.setPosition(CharPos.x - m_ControlOffset.x - (m_Circle.getRadius() / 2), CharPos.y + m_ControlOffset.y - (m_Circle.getRadius() / 2));

		m_AnchorPos = Vector2f(CharPos.x - m_AnchorOffset.x, CharPos.y + m_AnchorOffset.y);
		m_AnchorCircle.setPosition(m_AnchorPos);
		m_ControlPos = Vector2f(-m_ControlOffset.x + CharPos.x + (ControlPos.x / 100 * m_Circle.getRadius()), m_ControlOffset.y + CharPos.y + (ControlPos.y / 100 * m_Circle.getRadius()));
		m_ControlCircle.setPosition(m_ControlPos);
	}
	else
	{
		m_Circle.setPosition(CharPos.x + m_ControlOffset.x - (m_Circle.getRadius() / 2), CharPos.y + m_ControlOffset.y - (m_Circle.getRadius() / 2));

		m_AnchorPos = Vector2f(CharPos.x + m_AnchorOffset.x, CharPos.y + m_AnchorOffset.y);
		m_AnchorCircle.setPosition(m_AnchorPos);
		m_ControlPos = Vector2f(m_ControlOffset.x + CharPos.x + (ControlPos.x / 100 * m_Circle.getRadius()), m_ControlOffset.y + CharPos.y + (ControlPos.y / 100 * m_Circle.getRadius()));
		m_ControlCircle.setPosition(m_ControlPos);
	}


	float opposite = m_ControlCircle.getPosition().x - m_AnchorCircle.getPosition().x;
	float adjacent = m_ControlCircle.getPosition().y - m_AnchorCircle.getPosition().y;

	if(opposite > 0)
		m_WeaponRect.setRotation((atan(adjacent / opposite)) * 180 / b2_pi);
	else
		m_WeaponRect.setRotation(((atan(adjacent / opposite)) * 180 / b2_pi) + 180);

	m_WeaponRect.setPosition(m_ControlCircle.getPosition().x, m_ControlCircle.getPosition().y);

	m_HitCircle.setPosition(m_WeaponRect.getPosition().x + (cos(m_WeaponRect.getRotation() / 180 * 3.1415926) * hitBoxOffset), m_WeaponRect.getPosition().y + (sin(m_WeaponRect.getRotation() / 180 * b2_pi) * hitBoxOffset));
}


void Weapon::Draw(RenderWindow &Window, bool hitDebug)
{
	Window.draw(m_WeaponRect);
	if(hitDebug)
	{
		Window.draw(m_Circle);
		Window.draw(m_ControlCircle);
		Window.draw(m_AnchorCircle);
		//Window.draw(hitCircle);
	}
}