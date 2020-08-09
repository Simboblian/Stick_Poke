#include "Land.h"

sf::RectangleShape Land::GetShape()
{
	sf::RectangleShape result;

	result.setSize(_size);
	result.setPosition(_position);
	result.setOrigin(_origin);

	return result;
}

void Land::Draw(sf::RenderWindow &Window)
{
	for (int i = 0; i < _rectList.size(); i++)
		Window.draw(*_rectList[i], sf::RenderStates::Default);
}

void Land::Update(float Delta)
{
	_position = sf::Vector2f(Utility::B2VECtoSFVEC(_body->GetPosition(), true));

	for (int i = 0; i < _rectList.size(); i++)
		_rectList[i]->setPosition(sf::Vector2f(i * SIZE, 0) - _origin + _position);
}

Land::Land(b2World &World, sf::Vector2f Size)
{
	_size = Size;
	_origin = sf::Vector2f(Size.x / 2, Size.y / 2);
	_center = sf::Vector2f(_position.x, _position.y / 2);

	int capacity = ((int)_size.x - ((int)_size.x % SIZE)) / SIZE;

	for (int i = 0; i < capacity; i++)
	{
		sf::RectangleShape *r = new sf::RectangleShape();
		r->setSize(sf::Vector2f(SIZE, SIZE));
		r->setPosition(sf::Vector2f(i * SIZE, 0) - _origin + _position);
		if (i % 2 == 0)
			r->setFillColor(_color1);
		else
			r->setFillColor(_color2);
		_rectList.push_back(r);
	}
	
	InitSquareBody(World, _size);
	_body->SetType(b2_staticBody);
	_body->SetUserData((void*)ut::b_Land);
	_body->GetFixtureList()->SetUserData((void*)ut::f_Floor);

	SetPosition(sf::Vector2f(750, 100));
}

Land::Land()
{
}


Land::~Land()
{
}
