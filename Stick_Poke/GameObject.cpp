#include "GameObject.h"

void GameObject::CreateRoundedBody(b2World & World, sf::Vector2f Size)
{
	b2BodyDef _bodyDef;
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position.Set(0, 0);
	_bodyDef.fixedRotation = true;
	m_Body = World.CreateBody(&_bodyDef);
	CreateRoundedFixture(Size);
}

void GameObject::CreateSquareBody(b2World & World, sf::Vector2f Size)
{
	b2BodyDef _bodyDef;
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position.Set(0, 0);
	_bodyDef.fixedRotation = true;
	m_Body = World.CreateBody(&_bodyDef);
	CreateSquareFixture(Size);
}

void GameObject::CreateCircularBody(b2World & World, float Radius)
{
	b2BodyDef _bodyDef;
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position.Set(0, 0);
	m_Body = World.CreateBody(&_bodyDef);
	CreateCircleFixture(Radius);
}

void GameObject::CreateRoundedFixture(sf::Vector2f Size)
{
	sf::Vector2f _size = Size;
	sf::Vector2f _halfSize = sf::Vector2f(_size.x / 2, _size.y / 2);
	float _rounding = _halfSize.x / 4;

	b2Vec2 _vertices[8];
	_vertices[0].Set(-(_halfSize.x - _rounding) / ut::SCALE, -_halfSize.y / ut::SCALE);
	_vertices[1].Set((_halfSize.x - _rounding) / ut::SCALE, -_halfSize.y / ut::SCALE);
	_vertices[2].Set(_halfSize.x / ut::SCALE, -(_halfSize.y - _rounding) / ut::SCALE);
	_vertices[3].Set(_halfSize.x / ut::SCALE, (_halfSize.y - _rounding) / ut::SCALE);
	_vertices[4].Set((_halfSize.x - _rounding) / ut::SCALE, _halfSize.y / ut::SCALE);
	_vertices[5].Set(-(_halfSize.x - _rounding) / ut::SCALE, _halfSize.y / ut::SCALE);
	_vertices[6].Set(-_halfSize.x / ut::SCALE, (_halfSize.y - _rounding) / ut::SCALE);
	_vertices[7].Set(-_halfSize.x / ut::SCALE, -(_halfSize.y - _rounding) / ut::SCALE);

	b2PolygonShape _shape;
	_shape.Set(_vertices, 8);

	b2FixtureDef _fixtureDef;
	_fixtureDef.shape = &_shape;
	_fixtureDef.density = 1.0f;
	_fixtureDef.friction = 0.1f;
	m_Body->CreateFixture(&_fixtureDef);
}

void GameObject::CreateSquareFixture(sf::Vector2f Size)
{
	sf::Vector2f _size = Size;
	sf::Vector2f _halfSize = sf::Vector2f(_size.x / 2, _size.y / 2);

	b2PolygonShape _shape;
	_shape.SetAsBox(_halfSize.x / ut::SCALE, _halfSize.y / ut::SCALE);

	b2FixtureDef _fixtureDef;
	_fixtureDef.shape = &_shape;
	_fixtureDef.density = 1.0f;
	_fixtureDef.friction = 0.1f;
	m_Body->CreateFixture(&_fixtureDef);
}

void GameObject::CreateCircleFixture(float Radius)
{
	b2CircleShape _shape;
	_shape.m_radius = Radius / ut::SCALE;

	b2FixtureDef _fixtureDef;
	_fixtureDef.shape = &_shape;
	_fixtureDef.density = 1.0f;
	_fixtureDef.friction = 0.1f;
	m_Body->CreateFixture(&_fixtureDef);
}

void GameObject::Draw(sf::RenderWindow & Window)
{
}

void GameObject::Update()
{
}

void GameObject::Update(sf::Vector2f Gravity)
{
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
