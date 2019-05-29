#include "Land.h"

sf::RectangleShape Land::GetShape()
{
	sf::RectangleShape result;

	result.setSize(m_Size);
	result.setPosition(m_Position);
	result.setOrigin(m_Origin);

	return result;
}

void Land::Draw(sf::RenderWindow &Window)
{
	for (int i = 0; i < m_RectList.size(); i++)
		Window.draw(*m_RectList[i], sf::RenderStates::Default);
}

void Land::Update(sf::Vector2f Gravity)
{
}

Land::Land(sf::Vector2f Size)
{
	m_GravityScale = 0;

	m_Size = Size;
	m_Origin = sf::Vector2f(Size.x / 2, Size.y / 2);
	m_Position = sf::Vector2f(512, 706);
	m_Center = sf::Vector2f(m_Position.x, m_Position.y / 2);

	int capacity = ((int)m_Size.x - ((int)m_Size.x % SIZE)) / SIZE;

	for (int i = 0; i < capacity; i++)
	{
		sf::RectangleShape *r = new sf::RectangleShape();
		r->setSize(sf::Vector2f(SIZE, SIZE));
		r->setPosition(sf::Vector2f(i * SIZE, 0) - m_Origin + m_Position);
		if (i % 2 == 0)
			r->setFillColor(m_Color1);
		else
			r->setFillColor(m_Color2);
		m_RectList.push_back(r);
	}
}

Land::Land()
{
}


Land::~Land()
{
}
