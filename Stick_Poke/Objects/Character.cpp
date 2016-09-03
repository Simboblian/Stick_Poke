#include "Character.h"

void Character::Draw(RenderWindow &Window)
{
	//Window.draw(m_Rect);
}

void Character::Update()
{
	b2Vec2 worldCenter = m_Body->GetWorldCenter();
	m_Velocity = Vector2f(m_Body->GetLinearVelocity().x, 0.0f);

	if (Keyboard::isKeyPressed(Keyboard::A))
		m_Velocity.x = -1.0f;
	else if (Keyboard::isKeyPressed(Keyboard::D))
		m_Velocity.x = 1.0f;
	else
		m_Velocity.x = 0.0f;

	if (Keyboard::isKeyPressed(Keyboard::LShift))
		m_Body->ApplyLinearImpulse(b2Vec2(m_Velocity.x < 0 ? -10.0f : 10.0f, 0.0f), worldCenter, true);

	m_Body->ApplyLinearImpulse(b2Vec2(m_Velocity.x, m_Velocity.y), worldCenter, true);
	m_Position = Vector2f(m_Body->GetPosition().x * SCALE, m_Body->GetPosition().y * SCALE);
	//m_Position += m_Velocity;
	m_Rect.setPosition(m_Position);

}

Character::Character(b2World &World)
{
	m_Rect.setSize(Vector2f(50.0f, 75.0f));
	m_Rect.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_Rect.setPosition(m_Position);
	m_Rect.setFillColor(Color::Yellow);

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

	//CREATE CHAIN
	b2PolygonShape shape;
	shape.SetAsBox(0.6f, 0.125f);

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 20.0f;
	fd.friction = 0.2f;

	b2RevoluteJointDef jd;
	jd.collideConnected = false;

	const float32 y = 25.0f;
	b2Body* prevBody = m_Body;
	for (int32 i = 0; i < 5; ++i)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(0.5f + i, y);
		b2Body* body = World.CreateBody(&bd);
		body->CreateFixture(&fd);

		b2Vec2 anchor(float32(i), y);
		jd.Initialize(prevBody, body, anchor);
		World.CreateJoint(&jd);

		prevBody = body;
	}

	b2CircleShape cShape;
	cShape.m_radius = 1.5f;
	fd.shape = &cShape;
	fd.density = 1.0f;
	fd.friction = 0.2f;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(6.5f, y);
	b2Body* body = World.CreateBody(&bd);
	body->CreateFixture(&fd);
	b2Vec2 anchor(float32(5), y);
	jd.Initialize(prevBody, body, anchor);
	World.CreateJoint(&jd);
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
