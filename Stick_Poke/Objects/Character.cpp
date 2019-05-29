#include "Character.h"

void Character::Draw(RenderWindow &Window)
{
	Window.draw(m_Rect);
	m_Weapon->Draw(Window, true);
}

void Character::Update()
{
	b2Vec2 worldCenter = m_Body->GetWorldCenter();
	m_Velocity = Vector2f(m_Body->GetLinearVelocity().x, 0.0f);


	if (Joystick::getAxisPosition(0, Joystick::Axis::X) <= -20.0f)
		m_Velocity.x = -1.0f;
	else if (Joystick::getAxisPosition(0, Joystick::Axis::X) >= 20.0f)
		m_Velocity.x = 1.0f;
	else
		m_Velocity.x = 0.0f;

	if (Keyboard::isKeyPressed(Keyboard::LShift))
		m_Body->ApplyLinearImpulse(b2Vec2(m_Velocity.x < 0 ? -10.0f : 10.0f, 0.0f), worldCenter, true);

	Vector2f controller;
	controller.x = Joystick::getAxisPosition(0, Joystick::Axis::U);
	controller.y = Joystick::getAxisPosition(0, Joystick::Axis::V);

	m_Body->ApplyLinearImpulse(b2Vec2(m_Velocity.x, m_Velocity.y), worldCenter, true);
	m_Position = Vector2f(B2VECtoSFVEC(m_Body->GetPosition(), true));
	m_Rect.setPosition(m_Position);

	m_Weapon->Update(controller, m_Position, false, false);
}

Character::Character(b2World &World)
{
	m_Rect.setSize(Vector2f(50.0f, 100.0f));
	m_Rect.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_Rect.setPosition(m_Position);
	m_Rect.setFillColor(Color::Yellow);

	m_BackBicep.setSize(Vector2f(10.0f, 40.0f));
	m_BackBicep.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_BackBicep.setPosition(m_Position);
	m_BackBicep.setFillColor(Color::Red);

	m_BackBicep.setSize(Vector2f(10.0f, 40.0f));
	m_BackForearm.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_BackForearm.setPosition(m_Position);
	m_BackForearm.setFillColor(Color::Red);

	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;
	BodyDef.position = SFVECtoB2VEC(m_Position, true);
	m_Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(SFVECtoB2VEC(m_Rect.getSize(), true).x / 2, SFVECtoB2VEC(m_Rect.getSize(), true).y / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.filter.groupIndex = -1;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &Shape;
	fixtureDef.friction = 1.0f;
	m_Body->SetFixedRotation(true);
	m_Body->CreateFixture(&fixtureDef);

	m_Weapon = new Weapon();
	m_Weapon->SetAnchorOffset(Vector2f(-75.0, 15.0f));
	m_Weapon->SetControlRadius(50.0f);
	m_Weapon->SetControlOffset(Vector2f(75.0f, 0.0f));
	m_Weapon->SetWeaponSize(Vector2f(180.0, 10.0f));
	m_Weapon->SetWeaponOrigin(Vector2f(160.0, 5.0f));
	m_Weapon->SetHitboxOffset(Vector2f(15.0, 0.0f));
	m_Weapon->SetHitboxRadius(7.5f);

	m_State = STANDING;
}

Character::Character()
{
	m_Rect.setSize(Vector2f(50.0f, 75.0f));
	m_Rect.setOrigin(25.0f, 37.5f);
	m_Rect.setPosition(m_Position);
	m_Rect.setFillColor(Color::Yellow);
}

Character::~Character()
{
}
