#ifndef _UIPROJECTBAR_H
#define _UIPROJECTBAR_H

#include "UIObject.h"

class UIProgressBar : public UIObject
{
private:
	sf::RectangleShape m_Fill;
	sf::RectangleShape m_Outline;

	float m_Max;
	float m_Current;
	float m_FillPercent;

	bool m_AllowRegen;
	bool m_Regen;
	float m_RegenCount;
	float m_RegenMax;
public:
	void AllowRegen(float WaitTime);
	void StartRegen() { m_Regen = true; };
	void StopRegen() { m_Regen = false; m_RegenCount = 0; };
	bool IsFull() { return(m_Current == m_Max); };
	bool IsEmpty() { return(m_Current == 0); };

	void SetColour(sf::Color Colour) { m_Fill.setFillColor(Colour); };
	void SetMax(float Max) { m_Max = Max; m_Current = m_Max; };
	void SetCurrent(float Current) { m_Current = Current; if (m_AllowRegen) StopRegen(); };
	void SetSize(sf::Vector2f Size) { m_Size = Size; m_Fill.setSize(m_Size); m_Outline.setSize(m_Size); };
	void SetPosition(sf::Vector2f Position) { m_Position = Position; m_Fill.setPosition(m_Position); m_Outline.setPosition(m_Position); };

	float GetCurrent() { return m_Current; };

	void Update(sf::Vector2f Position);
	void Draw(sf::RenderWindow &Window);

	UIProgressBar();
	UIProgressBar(sf::Vector2f Position, sf::Vector2f Size);
	~UIProgressBar();
};

#endif
