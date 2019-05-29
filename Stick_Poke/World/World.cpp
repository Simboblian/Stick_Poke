#include "World.h"

void World::Update()
{
}

void World::Draw(RenderWindow &Window)
{
	for (int i = 0; i < m_RectList.size(); i++)
		Window.draw(*m_RectList[i], RenderStates::Default);
}

World::World()
{
}

World::World(b2World &World, Vector2f Size)
{
	m_Size = Size;
	m_Origin = Vector2f(Size.x / 2, Size.y / 2);
	m_Position = Vector2f(512, 706);
	m_Center = Vector2f(m_Position.x, m_Position.y / 2);

	int capacity = ((int)m_Size.x - ((int)m_Size.x % SIZE)) / SIZE;

	for (int i = 0; i < capacity; i++)
	{
		RectangleShape *r = new RectangleShape();
		r->setSize(Vector2f(SIZE, SIZE));
		r->setPosition(Vector2f(i * SIZE, 0) - m_Origin + m_Position);
		if (i % 2 == 0)
			r->setFillColor(m_Color1);
		else
			r->setFillColor(m_Color2);
		m_RectList.push_back(r);
	}

	b2BodyDef BodyDef;
	BodyDef.type = b2_staticBody;
	BodyDef.position = SFVECtoB2VEC(m_Position, true);
	m_Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(SFVECtoB2VEC(Size, true).x / 2, SFVECtoB2VEC(Size, true).y / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &Shape;
	fixtureDef.friction = 1.0f;
	m_Body->SetFixedRotation(true);
	m_Body->CreateFixture(&fixtureDef);
}

World::~World()
{
}
