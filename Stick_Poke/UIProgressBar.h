#ifndef _UIPROJECTBAR_H
#define _UIPROJECTBAR_H

#include "UIObject.h"

class UIProgressBar : public UIObject
{
private:
	sf::RectangleShape _fill;
	sf::RectangleShape _outline;

	float _max;
	float _current;
	float _fillPercent;

	bool _allowRegen;
	bool _regen;
	float _regenCount;
	float _regenMax;
public:
	void AllowRegen(float WaitTime);
	void StartRegen() { _regen = true; };
	void StopRegen() { _regen = false; _regenCount = 0; };
	bool IsFull() { return(_current == _max); };
	bool IsEmpty() { return(_current == 0); };

	void SetColour(sf::Color Colour) { _fill.setFillColor(Colour); };
	void SetMax(float Max) { _max = Max; _current = _max; };
	void SetCurrent(float Current) { _current = Current; if (_allowRegen) StopRegen(); };
	void SetSize(sf::Vector2f Size) { _size = Size; _fill.setSize(_size); _outline.setSize(_size); };
	void SetPosition(sf::Vector2f Position) { _position = Position; _fill.setPosition(_position); _outline.setPosition(_position); };

	float GetCurrent() { return _current; };

	void Update(sf::Vector2f Position);
	void Draw(sf::RenderWindow &Window);

	UIProgressBar();
	UIProgressBar(sf::Vector2f Position, sf::Vector2f Size);
	~UIProgressBar();
};

#endif
