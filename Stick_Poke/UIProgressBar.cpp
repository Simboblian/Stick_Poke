#include "UIProgressBar.h"


void UIProgressBar::Update(sf::Vector2f Position)
{
	if (_current > _max)
		_current = _max;
	else if (_current < 0)
		_current = 0;

	_fillPercent = (_current / _max);

	SetPosition(Position);

	_fill.setSize(sf::Vector2f(_outline.getSize().x * _fillPercent, _outline.getSize().y));

	if (_allowRegen)
	{
		if (_regen)
		{
			if (_regenCount >= _regenMax)
			{
				_current++;
			}
			else
			{
				_regenCount++;
			}

			if (_current >= _max)
			{
				StopRegen();
			}
		}
	}
}

void UIProgressBar::AllowRegen(float WaitTime)
{
	_allowRegen = true;
	_regenMax = WaitTime;
	_regenCount = 0;
}

void UIProgressBar::Draw(sf::RenderWindow &Window)
{
	Window.draw(_fill);
	Window.draw(_outline);
}

UIProgressBar::UIProgressBar()
{
}

UIProgressBar::UIProgressBar(sf::Vector2f Position, sf::Vector2f Size)
{
	_outline.setFillColor(sf::Color::Transparent);
	_outline.setOutlineColor(sf::Color::White);
	_outline.setOutlineThickness(1.0f);
	_outline.setSize(Size);
	_outline.setOrigin(Size.x / 2, Size.y / 2);
	_outline.setPosition(Position);

	_fill.setFillColor(sf::Color::White);
	_fill.setOutlineColor(sf::Color::Transparent);
	_fill.setSize(Size);
	_fill.setOrigin(Size.x / 2, Size.y / 2);
	_fill.setPosition(Position);

	_allowRegen = false;
	_regenMax = 0;
	_regenCount = 0;
}


UIProgressBar::~UIProgressBar()
{
}
