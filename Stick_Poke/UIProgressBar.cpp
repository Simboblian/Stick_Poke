#include "UIProgressBar.h"


void UIProgressBar::Update(sf::Vector2f Position)
{
	if (m_Current > m_Max)
		m_Current = m_Max;
	else if (m_Current < 0)
		m_Current = 0;

	m_FillPercent = (m_Current / m_Max);

	SetPosition(Position);

	m_Fill.setSize(sf::Vector2f(m_Outline.getSize().x * m_FillPercent, m_Outline.getSize().y));

	if (m_AllowRegen)
	{
		if (m_Regen)
		{
			if (m_RegenCount >= m_RegenMax)
			{
				m_Current++;
			}
			else
			{
				m_RegenCount++;
			}

			if (m_Current >= m_Max)
			{
				StopRegen();
			}
		}
	}
}

void UIProgressBar::AllowRegen(float WaitTime)
{
	m_AllowRegen = true;
	m_RegenMax = WaitTime;
	m_RegenCount = 0;
}

void UIProgressBar::Draw(sf::RenderWindow &Window)
{
	Window.draw(m_Fill);
	Window.draw(m_Outline);
}

UIProgressBar::UIProgressBar()
{
}

UIProgressBar::UIProgressBar(sf::Vector2f Position, sf::Vector2f Size)
{
	m_Outline.setFillColor(sf::Color::Transparent);
	m_Outline.setOutlineColor(sf::Color::White);
	m_Outline.setOutlineThickness(1.0f);
	m_Outline.setSize(Size);
	m_Outline.setOrigin(Size.x / 2, Size.y / 2);
	m_Outline.setPosition(Position);

	m_Fill.setFillColor(sf::Color::White);
	m_Fill.setOutlineColor(sf::Color::Transparent);
	m_Fill.setSize(Size);
	m_Fill.setOrigin(Size.x / 2, Size.y / 2);
	m_Fill.setPosition(Position);

	m_AllowRegen = false;
	m_RegenMax = 0;
	m_RegenCount = 0;
}


UIProgressBar::~UIProgressBar()
{
}
